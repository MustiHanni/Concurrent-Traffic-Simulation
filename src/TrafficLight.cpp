#include <iostream>
#include <random>
#include "TrafficLight.h"

#define RANDOM_MIN 4
#define RANDOM_MAX 6

int getRandomValue ()
{
    rand() % ((RANDOM_MAX - RANDOM_MIN) + 1) + RANDOM_MIN;
}

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
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 

    // launch vehicle queue processing in a thread
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 

    auto lastCycleTime = std::chrono::system_clock::now();

    // get random duration between 4 and 6 seconds
    int cycleDuration = getRandomValue();
    while (1)
    {
        // for the cpu sake..
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // get elapsed time since lastCycleTime
        int elapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - lastCycleTime).count();
        if (cycleDuration < elapsed)
        {
            // update lastCycleTime and random duration
            cycleDuration = getRandomValue();
            lastCycleTime = std::chrono::system_clock::now();

            // toggls the current phase
            _currentPhase = (_currentPhase == TrafficLightPhase::red) ? TrafficLightPhase::green : TrafficLightPhase::red;
        }
    }
}
