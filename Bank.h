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
#include "Metrics.h"
extern Metrics* metrics;

class Bank {
public:

	/**
	 * Function: Constructor
	 * Description: Instantiates the customer queue and tellers.
	 *
	 * @param t A ptr to the system timer.
	 */
	Bank(TimerSys* t);

	/**
	 * Function: Destructor
	 * Description: Deletes the tellers and the customer queue and the metrics object upon desctruction.
	 */
	virtual ~Bank();

	/**
	 * Function: openAndRunBank()
	 * Description: Opens the bank, starts running the global timer, and
	 * 				adds customers to queue while bank is open. When bank is
	 * 				operating hours end, closes the bank.
	 */
	void openAndRunBank();

	/**
	 * Function: closeBank()
	 * Description: Closes the bank by first telling the tellers to finish the remaining
	 * 				customers in the queue and clean themselves up. Then, it stops the timer.
	 */
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
