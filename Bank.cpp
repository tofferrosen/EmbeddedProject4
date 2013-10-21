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

#include "Bank.h"

const float scaledMinute = 0.1000;
const int sevenHoursInMins = 420; // 7 (num of hours) * 60 minutes (hours)
const int secsInHour = 60;

/**
 * Constructor
 * Initializes the customer queue and the tellers
 */
Bank::Bank() {
	Queue queue = new Queue();
	tellers = new teller[numOfTellers];

	// instantiate the tellers
	for(int i = 0; i < numOfTellers; i++){
		Teller teller = new Teller(queue);
		tellers[i] = teller;
	}
}

/**
 * Close the bank
 */
void Bank::closeBank(){
	int currentTimeSec;
	int timeToCloseSec;
	time_t timer;
	struct tm y2k;

	y2k.tm_hour = 0; y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	// Let the tellers know we are closed
	for(int i = 0; i < numOfTellers; i++){
		Teller teller = tellers[i];
		teller.stopWorking();
	}

	time(&timer); // get current time
	currentTimeSec = difftime(timer,mktime(&y2k)); // seconds since y2k
	timeToCloseSec = currentTime + (sevenHoursInMins * scaledMinute * secsInHours);
	while(currentTimeSec < timeToCloseSec){

	}

}

/**
 * Open the bank
 */
void Bank::openBank(){

	// Open for business! Put the tellers to work
	for(int i = 0; i < numOfTellers; i++){
		Teller teller = tellers[i];
		teller.startWorking();
	}

	// Add customers until close time

}

Bank::~Bank() {
	// TODO Auto-generated destructor stub
}
