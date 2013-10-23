/*
 * TimerSys.cpp
 *
 * This class represents the system timer.
 * Encapsulates a timer thread.
 */
#include "TimerSys.h"

/**
 * Function: Constructor
 * Description: Initalizes the timer.
 *
 * @param duration: The total duration of the timer, the point it starts decrementing.
 * @param sim_spped: The simulation speed.
 */
TimerSys::TimerSys( int duration, float sim_speed ){
	// Define length of the down counter:
	timerVal = duration;

	// Define speed at which the timer will decrement:
	speed = sim_speed;

	// Disable timer:
	timerOn = false;
	inRunMode = false;

	// Instantiate the pthread for later use:
	pthread_mutex_init(&mutex, NULL);
}// TimerSys()

TimerSys::~TimerSys(){/* Unused */}

/**
 * Function: startTimer()
 * Description: Starts the timer and creats the thread.
 */
void TimerSys::startTimer(){
	timerOn = true;
	inRunMode = true;
	pthread_create(&thread, NULL, TimerThreadFunc, this);
}

/**
 * Function: readTimer()
 * Description: Reads the current time of the timer
 *
 * @return int current value of the timer
 */
int TimerSys::readTimer(){
	return timerVal;
}

/**
 * Function: stopTimer()
 * Description: Stops the timer and cleans the timer thread.
 */
void TimerSys::stopTimer(){
	timerOn = false;
	pthread_join(thread,NULL);
}

/**
 * Function: isRunning()
 * Description: Checks whether the timer is still running
 *
 * @return bool true if timer is still running
 */
bool TimerSys::isRunning(){
	return inRunMode;
}

/**
 * Function: timerDecrementer()
 * Description: Decrements the timer. This is the function passed into
 * 				the thread. Stops when timer is shut off.
 */
void TimerSys::timerDecrementer(){

	while(timerOn == true){
		usleep(speed);
		timerVal-=TIME_INCR;

		if(timerVal <= 0){
			inRunMode = false;
		}

	}
}// timerDecrementer()
