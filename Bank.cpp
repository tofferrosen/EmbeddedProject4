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

static unsigned int bankOpenSec = 420;

/**
 * Constructor
 * Initializes the customer queue and the tellers
 */
Bank::Bank() {
	customerQueue = new Queue();

	// instantiate the tellers
	for(int i = 0; i < numOfTellers; i++){
		tellers[i] = new Teller(customerQueue);
	}
}

/**
 * Creates the timer thread
 * Starts running the timer
 */
void Bank::runTimer(){
	pthread_create(&timer, NULL, TimerThreadFunc, this);
}

/**
 * Opens the bank, starts running the global timer, and
 * adds customers to queue.
 */
void Bank::openAndRunBank(){
	time_t timer;
	time_t start = clock();

	// Open for business! Put the tellers to work
	for(int i = 0; i < numOfTellers; i++){
		Teller *teller = tellers[i];
		teller->startWorking();
	}

	runTimer(); // start the timer

	timer = clock();
	printf("Start time is: %d\n", difftime(start,timer));
	while(bankOpenSec > 0){

		int newCustomerEntryTime = (rand()%(240-60))+60; // random # between 1 to 4 minutes in seconds
		usleep(newCustomerEntryTime*1000);

		// Add customer to queue!!
		customerQueue->enqueue(new Customer(clock()));;
	}

	closeBank();
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

	printf("\nThe bank has closed");
}

/*
 * Decrements the bankOpenSec every second.
 */
void Bank::timerDecrementer(){

	while(true){
		usleep(100000);
		bankOpenSec--;
	}
}

Bank::~Bank() {
	// delete the tellers
	for(int i = 0; i < numOfTellers; i++){
		delete(tellers[i]);
	}

	// delete the customer queue
	delete(customerQueue);

}
