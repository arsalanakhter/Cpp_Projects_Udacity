# Cpp_Projects_Udacity

This repository contains the projects that I did for the Udacity Nanodegree proogram for C++. The C++ Udacity Nanodegree Program discusses foundations and Object Oriented Programming and goes upto concepts in Memory Management and Concurrency. Each module then has a final project, for which boilerplate code is given to the students, with tasks identified in the code which are needed to be completed for successful completion.

### Foundations - Project: Route Planning
In the Route Planning project, A* search algorithm is implemented and then used to find shortest distance between two points. This is then demonstrated on real-world map data from [Open StreetMap Project](https://www.openstreetmap.org/#map=5/38.007/-95.844 "Open Street Map"). 

### Object-Orineted Programming - Project: System Monitor
In the System Monitor Project, we build a Linux System Monitor, (similar to [htop](https://linux.die.net/man/1/htop)), using data from `/proc` directory in Linux. The project required knowing concepts such as Classes, Inheritance as well as file I/O to read processor as well as process data from `/proc` directory and displaying it on linux terminal interactively.

### Memory Management - Project: Memory Management of a ChatBot
This project contains a chatbot that could reply to user input. The goal of the project is to manage the memory utilized by the chatbot on heap using smart pointers and reduce memory leaks. The project required knowledge of smart pointers introduced in the C++11 standard as well as concepts such as difference between stack and heap, memory leaks, usage of memory manipulating tools from `malloc/free`, `new/delete` to managing unique or shared resources using `unique_ptr`, `shared_ptr` and `weak_ptr` in C++11 Standard Template Library (STL) 

## Concurrency - Project: Traffic Simulator
This project aims to simulate vehicles using a multi-threaded simulator where each vehicle is running in its own thread. Moreover, other items in the simulation such as streets and intersections are running their own threads, and the idea is to manage the resources using mutexes and locks as well as condiiton variables and message queues. 
