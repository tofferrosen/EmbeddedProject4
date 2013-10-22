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



class Bank {
public:
	Bank();
	virtual ~Bank();

	void openAndRunBank();
	void closeBank();

private:
	static const int numOfTellers = 3;
	Teller* tellers[numOfTellers];
	Queue* customerQueue;
	bool open;

};

#endif /* BANK_H_ */
