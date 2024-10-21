# 42-philosophers
A project about concurrent programming, focusing on multithreading.

![image](https://github.com/user-attachments/assets/7fe300b7-3793-4849-9f45-2a09611be228)


## Preamble
I say this with many of the Hive projects, but I'll say it again here: this is a great project! It isn't as big as the other project in the same curriculum circle (look into the 42 Holy Graph to learn what I'm talking about), but it is really interesting. The big new concept that this project taught is _multithreading_. And just like so many other programming concepts, it sounds a lot more complex and daunting than it actually is.

## The Idea of the Project
Let's imagine a round table with food on it. There's an indeterminate amount of philosophers around the table. For every philosopher, there is a fork on the table as well. 
The philosophers must eat inside a certain timeframe or they'll starve. The philosophers can be in three mutually exclusive states: they are either thinking, they're eating or then they are asleep. After a philosopher eats, they go to sleep, after which they start thinking, which means they're ready eat again and so on.

The problem is that the philosophers require _two forks_ to eat the food. This means that they need one of their neighbours' forks to eat, and at any one time there are some who are able to eat and some who aren't. The philosophers cannot communicate with each other, and they have no knowledge of who is closest to starving. The goal is to come up with a system that keeps all the philosophers around the table alive as long as is possible.

As you might have already guessed, the philosophers around the table are threads, and the forks that they share are variables in the process that all the threads have access to, but that only one thread can use at a time.

## But What Even Are Threads?
While we've talked earlier about processes (check out my 42-Pipex's ReadMe), we haven't touched on threads yet. Whereas a process is an instance of a program in execution, _a thread is the smallest unit of execution in a process_. A process can contain multiple threads, which share the same memory space but have their own stack and local variables. 

![image](https://github.com/user-attachments/assets/335f8b83-b7d2-4b1a-8c83-ac137fb1c955)

Threads can be in various states, such as new, running and blocked.

## Potential Issues in Multithreading
While multithreading can improve performance and responsiveness, it also introduces several potential issues. These issues have to do with the fact that a process's threads share the same memory space. Here's a few of these issues:
- Race Conditions: A race condition occurs when multiple threads access and modify shared data concurrently, and the final outcome depends on the timing of their execution. This can lead to undefined behaviour, data corruption or crashes. Race conditions are sure to happen in this project, especially when you have a couple of hundred philosophers trying to access the same variables.
- Deadlocks: A deadlock occurs when two or more threads are waiting for each other to release a resource, preventing any progress. This is something that we wish to avoid when it comes to the philosophers and their forks.
- Data Inconsistency: When multiple threads read and write shared data without proper synchronization, it can result in inconsistent or corrupted data. For example, one thread might be reading a value while another is updating it, which causes the thread reading the value to get a partially updated value.

How can we avoid these issues that arise in multithreading?

## Mutexes
A _mutex_ (short for "mutual exclusion") is a synchronization primitive used to prevent concurrent access to shared resources, ensuring that only one thread can access the resource at a time.

A mutex is essential a lock that can be acquired and released by a thread. When a thread wants to access a shared resource, it must first acquire the mutex lock. If the mutex is already locked by another thread, the requesting thread must wait until the mutex is released. Once the thread is done with the shared resource, it releases the mutex, allowing other threads to acquire it.

In C, mutexes are often implemented using the POSIX Threads (Pthreads) library. In this project every fork is a mutex, but mutexes are used with other things as well, as can be seen in the next section.

## Breaking Down the Project
This project has basically two parts to it:
1. Setting everything up for the simulation based on the arguments passed to the program.
2. Running the actual simulation.

There isn't really anything new in the first part when compared to earlier projects. It's all the usual stuff: parsing the given arguments, mallocing the amount of philosopher variables that the first argument demands and setting the time-limits for each of action like the time to eat, the time to sleep and the time to die. What is somewhat interesting is what exactly is set-up. For each philosopher, there is a thread (the actual philosopher) and a struct that holds all the data about the philosopher (what was the last time the philosopher ate, how many times have they eaten, etc.). Besides the philosopher threads, there is also a monitoring thread that, as the name implies, _monitors_ the simulation. It is the monitoring thread that starts and ends the simulation and checks if a philosopher has died.

The really interesting stuff happens when the simulation is actually running. Every philosopher thread will follow the same routine of thinking and trying to grab forks, eating, falling asleep and thinking again. The only difference between the philosophers is that in the very start of the simulation every other philosopher starts their routine with a slight delay. This makes it possible for each philosophers to have the requisite amount of forks available for eating. If every philosopher would try to access the forks available for them right away, it would cause cause deadlocks and general chaos, and the simulation would end almost immediately, but by having every other philosopher start with a delay, we can have the two 'groups' of philosophers working in two different cycles that make it possible for each philosopher to have enough time to grab their forks while the philosophers next to them are sleeping and vice versa.

Every variable that can be modified by a thread but which can be accessed by more than one thread is protected by a mutex. For example, because the monitoring thread checks the last_time_eaten variable in a philosopher structure, which a philosopher thread can itself modify, it needs to be protected by a mutex.

## Points of Improvement
Looking back at this project, I can see many areas for improvement. One obvious area is how I set up the data structure for the philosopher structs: I used a linked list, even though it would have been much better to use an array. Just from the setup speed perspective, it's quite slow to malloc each philosopher struct individually when I could have just allocated an entire array of them at once. An even faster implementation would have been to allocate a large array of philosophers in the data structure from the start and then using only the amount specified by the first argument. This way, the philosophers would be stored on the stack instead of the heap. However, this approach would feel somewhat cheap, as the number of philosophers would be hardcoded into the program.

Another improvement would be the removal of the monitoring thread. I don't really remember why I thought that the monitoring thread was necessary at the time. Why create another thread for monitoring when I could have just used the main thread itself?

But while there are these types of points of improvement in the project, I must say that I'm all in all quite happy with how it turned out.

## Prerequisites and How to Run Program
To run the program, you must have the following:
1. A Linux-based system
2. GNU Make
3. GCC compiler

If you have all the prerequisites, do the following:
1. git clone the repository:
   > git clone [repository-url]

2. Go to the /philo directory:
   > cd [repository-root]/philo/
  
3. Call 'make':
   > make

4. Run the program with the following arguments:
   > ./philo [philosopher amount] [milliseconds to die] [milliseconds to eat] [milliseconds to sleep] [amount of meals (OPTIONAL)]

You can run the program with whatever arguments you want. To really test the program it is recommended to try:
> ./philo 200 130 60 60

These were the arguments we used to really test each other' simulations during the evaluations. Generally the goal was that the simulation shouldn't end too early, but it can be a thing of chance of how long the simulation continues (sometimes I've had the simulation run for over 10 minutes without any signs of stopping, sometimes it has stopped after only a dozen seconds or so, but generally it has continued for a satisfactory amount of time). To get the best results, close all background processes that can slow down the computer.

Enjoy!
