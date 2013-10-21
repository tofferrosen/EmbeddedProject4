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

const int numOfTellers = 3;

class Bank {
public:
	Bank();
	virtual ~Bank();

	void openBank();
	void closeBank();

private:
	Teller tellers[];
	Queue customerQueue;
	bool open;

};

#endif /* BANK_H_ */
