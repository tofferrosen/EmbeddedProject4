/*
 * Bank.cpp
 *
 *	The simulation time is scaled such that 100 milliseconds of absolute clock time
 *	represents 1 minute of simulation clock time
 *
 *	Open between 9:00am to 4:00pm - so open for 7 hours
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */

#include <Bank.h>

const float scaledMinute = 0.1000;
const int sevenHoursInMins = 420; // 7 (num of hours) * 60 minutes (hours)
const int secsInHour = 60;

/**
 * Constructor
 * Initializes the customer queue and the tellers
 */
Bank::Bank() {
	customerQueue = new Queue();

	// instantiate the tellers
	for(int i = 0; i < numOfTellers; i++){
		Teller *teller = new Teller(customerQueue);
		tellers[i] = teller;
	}
}

/**
 * Opens the bank
 */
void Bank::openAndRunBank(){
	int currentTimeSec;
	int timeToCloseSec;
	int newCustomerInterval;
	int timeAddCustomer;
	time_t timer;
	struct tm y2k;

	y2k.tm_hour = 0; y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	// Open for business! Put the tellers to work
	for(int i = 0; i < numOfTellers; i++){
		Teller *teller = tellers[i];
		teller->startWorking();
	}

	time(&timer); // get current time
	currentTimeSec = difftime(timer,mktime(&y2k)); // seconds since y2k
	timeToCloseSec = currentTimeSec + (sevenHoursInMins * scaledMinute * secsInHour);
	newCustomerInterval = rand() % 60 + 240; // random # between 1 to 4 minutes in seconds
	timeAddCustomer = currentTimeSec + newCustomerInterval;

	// operate within open hours
	while(currentTimeSec < timeToCloseSec){
		time(&timer);
		currentTimeSec = difftime(timer,mktime(&y2k));

		// Add customer
		if(currentTimeSec >= timeAddCustomer){
			customerQueue->enqueue(new Customer(currentTimeSec));

			// update next time to add customer
			newCustomerInterval = rand() % 60 + 240;
			timeAddCustomer = currentTimeSec + newCustomerInterval;
		}
	}
}

/**
 * Open the bank
 */
void Bank::closeBank(){

	// Open for business! Put the tellers to work
	for(int i = 0; i < numOfTellers; i++){
		Teller *teller = tellers[i];
		teller->stopWorking();
	}
}

Bank::~Bank() {
	// delete the tellers
	for(int i = 0; i < numOfTellers; i++){
		delete(tellers[i]);
	}
	// delete the array
	delete(tellers);

	// delete the customer queue
	delete(customerQueue);

}
