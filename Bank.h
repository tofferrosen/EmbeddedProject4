/*
 * Bank.h
 *
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */

#ifndef BANK_H_
#define BANK_H_

#include <teller.h>
#include <queue.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <Constants.h>
#include <TimerSys.h>

class Bank {
public:
	Bank(TimerSys* t);
	virtual ~Bank();
	void openAndRunBank();
	void closeBank();

private:
	Teller* tellers[NUM_TELLERS];
	Queue* customerQueue;
	bool open;
	bool timerOn;
	pthread_t thread;
	TimerSys* timer;
};

#endif /* BANK_H_ */
