#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

/* 
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
}
*/

/* Implementation of class "TrafficLight" */

 
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
    // initialize the loop cycle
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist46(4,6);
    _loop_end_time = std::chrono::high_resolution_clock::now() + std::chrono::seconds(dist46(rng));
}

/*
void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
}
*/
TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}
/*
void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should 
    //be started in a thread when the public method „simulate“ is called.
    // To do this, use the thread queue in the base class. 
}
*/
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
        if (time_now > _loop_end_time)
        {
            _loop_end_time = time_now + std::chrono::seconds(dist46(rng));
            switch(_currentPhase)
            {
                case TrafficLightPhase::red : _currentPhase = TrafficLightPhase::green;
                case TrafficLightPhase::green : _currentPhase = TrafficLightPhase::red;
                default: _currentPhase = TrafficLightPhase::red;
            }
        }
    }
}

