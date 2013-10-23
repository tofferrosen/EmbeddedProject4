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


Bank::Bank(){
	customerQueue = new Queue();

	// Instantiate the tellers:
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

	while(true){
		int newCustomerEntryTime = ((rand()%(240-60))+60); // random # between 1 to 4 minutes in sim seconds
		//printf("----> Adding customer in: %d\n", newCustomerEntryTime);

		usleep((int)( newCustomerEntryTime * SIMULATED_SEC_SCALE ));
		if(bankOpenSec > 0){
			// Add customer to queue!!
			Customer* c = new Customer(bankOpenSec);
			customerQueue->enqueue(c);
		}else{
			break;
		}
	}
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
	stopTimer();
	printf("This fabulous bank has closed!\n");

	printf("Customers Served:\t %d\n", metrics->getNumCustomers());
	printf("Average time in queue: \t %d\n", metrics->getAvgCustWaitTime());
	printf("Maximum time in queue: \t %d\n", metrics->getMaxDepth());
	printf("Average time at teller:\t %d\n", metrics->getAvgTellerWaitTime());
	printf("Maximum time at teller:\t %d\n", metrics->getMaxTellerWaitTime());
	printf("Average service time is:\t %d\n", metrics->getAvgServiceTime());
/** ??
	printf("# ------------------------------------------------------------- #\n\
			The fabulous bank has closed, we apologize for the inconvenience!\n\
			# ------------------------------------------------------------- #\n\
		Customers Serviced:\t%d\n\n\
		Maximum Depth Of The Queue:\t%d\n\n\
		Average Time In Queue:\t%f\n\
		Maximum Time In Queue:\t%d\n\n\
		Average Time At Teller:\t%f\n\
		Maximum Time At Teller:\t%d\n\n\
		Average Teller Wait Time:\t%f\n\
		Maximum Teller Wait Time:\t%d\n\n",
			metrics->getNumCustomers(),
			metrics->getMaxDepth(),
			metrics->getAvgCustWaitTime(),
			metrics->getMaxCustWaitTime(),
			metrics->getAvgServiceTime(),
			metrics->getMaxServiceTime(),
			metrics->getAvgTellerWaitTime(),
			metrics->getMaxTellerWaitTime()); **/
}

/*
 * Decrements the bankOpenSec every second.
 */
void Bank::timerDecrementer(){

	while(timerOn == true){
		usleep((int)(SIMULATED_SEC_SCALE));
		bankOpenSec--;
	}
}

Bank::~Bank() {
	// Delete the tellers
	for(int i = 0; i < numOfTellers; i++){
		delete(tellers[i]);
	}

	// Delete the customer queue
	delete(customerQueue);
	delete(metrics);
}
