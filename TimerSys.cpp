/*
 * TimerSys.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: cbr4830
 */
#include "TimerSys.h"

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

void TimerSys::startTimer(){
	timerOn = true;
	inRunMode = true;
	pthread_create(&thread, NULL, TimerThreadFunc, this);
}

int TimerSys::readTimer(){
	/*while(pthread_mutex_trylock(&mutex) != 0){
		usleep(10); // to not lock CPU
	}*/
	//pthread_mutex_lock(&mutex);
	return timerVal;
	//pthread_mutex_unlock(&mutex);
}

void TimerSys::stopTimer(){
	timerOn = false;
	pthread_join(thread,NULL);
}
bool TimerSys::isRunning(){
	return inRunMode;
}

void TimerSys::timerDecrementer(){

	while(timerOn == true){
		usleep(speed);
		timerVal-=TIME_INCR;
		printf("Time %d\n",timerVal);
		if(timerVal <= 0){
			inRunMode = false;
		}

	}
}// timerDecrementer()
