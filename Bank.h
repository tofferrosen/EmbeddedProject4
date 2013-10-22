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

class Bank {
public:
	Bank();
	virtual ~Bank();
	void openAndRunBank();
	void closeBank();
	void timerDecrementer();
	void runTimer();


private:
	static void * TimerThreadFunc(void * This) {((Bank *)This)->timerDecrementer(); return NULL;};
	static const int numOfTellers = 3;
	Teller* tellers[numOfTellers];
	Queue* customerQueue;
	bool open;
	pthread_t timer;


};

#endif /* BANK_H_ */
