#include <iostream>
#include <random>
#include <future>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

 
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex>
    // and _condition.wait() 
    // to wait for and receive new messages and 
    // pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function.
    std::unique_lock<std::mutex> uLock(_mutex);
    _cond.wait(uLock, [this] { return !_messages.empty(); }); // pass unique lock to condition variable

    // remove last vector element from queue
    T msg = std::move(_messages.back());
    _messages.pop_back();

    return msg; // will not be copied due to return value optimization (RVO) in C++ 
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the 
    // mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add
    // a new message to the queue and afterwards 
    // send a notification.
    // perform queue modification under the lock

    // simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // add vector to queue
    std::cout << "   Message " << msg << " has been sent to the queue" << std::endl;
    _messages.push_back(std::move(msg));
    _cond.notify_one(); // notify client after pushing new Vehicle into vector
}


/* Implementation of class "TrafficLight" */

 
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
    _msg_queue = std::make_shared<MessageQueue<TrafficLightPhase>>();
    // initialize the loop cycle
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist46(4,6);
    _loop_end_time = std::chrono::high_resolution_clock::now() + std::chrono::seconds(dist46(rng));
}


void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        auto msg = _msg_queue->receive();
        if (msg == TrafficLightPhase::green)
            return;
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should 
    //be started in a thread when the public method „simulate“ is called.
    // To do this, use the thread queue in the base class. 
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that 
    // measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between 
    // red and green and sends an update method 
    // to the message queue using move semantics. The cycle 
    // duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for 
    // to wait 1ms between two cycles. 

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist46(4,6);

    while(1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        auto time_now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_seconds = _loop_end_time - time_now;
        if (diff_seconds.count() < 0.0)
        {
            _loop_end_time = time_now + std::chrono::seconds(dist46(rng));
            if (_currentPhase == TrafficLightPhase::green) _currentPhase = TrafficLightPhase::red; 
            else if (_currentPhase == TrafficLightPhase::red) _currentPhase = TrafficLightPhase::green; 
            else std::cout << "There is some issue in cycleThroughPhases. \n";
            auto update = _currentPhase;
			auto sent_update_future = std::async(std::launch::async, 
                                                &MessageQueue<TrafficLightPhase>::send, 
                                                _msg_queue, std::move(update));
			sent_update_future.wait();
        }
    }
}

