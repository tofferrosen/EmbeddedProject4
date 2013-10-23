/**
 * TimerSys.h
 *
 * Created on: Oct 23, 2013
 *      Author: cbr4830
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "Constants.h"

#ifndef TIMERSYS_H_
#define TIMERSYS_H_

class TimerSys{
public:
	TimerSys( int duration, float sim_speed );
	virtual ~TimerSys(void);
	int readTimer(void);
	bool isRunning(void);
	void startTimer(void);
	void timerDecrementer();
	void stopTimer(void);
private:
	static void * TimerThreadFunc(void * This) {((TimerSys *)This)->timerDecrementer(); return NULL;};
	bool timerOn;
	pthread_t thread;
	pthread_mutex_t mutex;
	int timerVal;
	float speed;
	bool inRunMode;
};

#endif /* TIMERSYS_H_ */
