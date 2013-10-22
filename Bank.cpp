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

static int bankOpenSec = 420;

/**
 * Constructor
 * Initializes the customer queue and the tellers
 */
Bank::Bank() {
	customerQueue = new Queue();

	// instantiate the tellers
	for(int i = 0; i < numOfTellers; i++){
		tellers[i] = new Teller(customerQueue,i+1);
	}
}

/**
 * Creates the timer thread
 * Starts running the timer
 */
void Bank::runTimer(){
	timerOn = true;
	pthread_create(&thread, NULL, TimerThreadFunc, this);
}

/**
 * Opens the bank, starts running the global timer, and
 * adds customers to queue.
 */
void Bank::openAndRunBank(){

	printf("This fabulous bank has opened!\n");

	// Open for business! Put the tellers to work
	for(int i = 0; i < numOfTellers; i++){
		Teller *teller = tellers[i];
		teller->startWorking();
	}

	runTimer(); // start the timer
	while(bankOpenSec > 0){

		int newCustomerEntryTime = (rand()%(240-60))+60; // random # between 1 to 4 minutes in seconds
		usleep(newCustomerEntryTime*1000);
		printf("     GLOBAL TIME: %d\n", bankOpenSec);

		// Add customer to queue!!
		customerQueue->enqueue(new Customer(clock()));;
	}

	printf("     AFTER WHILE\n");
	closeBank();
}

void Bank::stopTimer(){
	timerOn = false;
	pthread_join(thread,NULL);
}

/**
 * Close the bank
 */
void Bank::closeBank(){

	for(int i = 0; i < numOfTellers; i++){
		Teller *teller = tellers[i];
		teller->stopWorking();
	}

	printf("Closing timer\n");
	stopTimer();
	printf("The bank has closed, we apologize for the inconvenience!");
}

/*
 * Decrements the bankOpenSec every second.
 */
void Bank::timerDecrementer(){

	while(timerOn == true){
		usleep(100000);
		//usleep(10000);
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
