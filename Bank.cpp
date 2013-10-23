/**
 * Bank.cpp
 *
 * The simulation time is scaled such that 100 milliseconds of absolute clock time
 * represents 1 minute of simulation clock time.
 * Open between 9:00am to 4:00pm - so open for 7 hours
 *
 * Created on: Oct 16, 2013
 * Author: cbr4830
 */

#include "Bank.h"

Bank::Bank(TimerSys* t){
	// Store Reference To Timer:
	timer = t;

	// Create New Customer Queue:
	customerQueue = new Queue();

	// Instantiate Tellers:
	for(int i = 0; i < NUM_TELLERS; i++){
		tellers[i] = new Teller(customerQueue,i+1,timer);
	}
}

/**
 * Opens the bank, starts running the global timer, and
 * adds customers to queue.
 */
void Bank::openAndRunBank(){

	printf("This fabulous bank has opened!\n");

	// Is Empty:
	customerQueue->printQueue();
	printf("Is Empty? %d\n", customerQueue->empty());
	// Has 1 Element:
	customerQueue->enqueue(new Customer(100));
	customerQueue->printQueue();

	// Has 3 Elements:
	customerQueue->enqueue(new Customer(200));
	customerQueue->enqueue(new Customer(300));
	customerQueue->printQueue();

	// Dequeue 1:
	customerQueue->pop();
	customerQueue->printQueue();

	// Dequeue All:
	customerQueue->pop();
	customerQueue->pop();
	customerQueue->printQueue();

	// Dequeue While Empty:
	customerQueue->pop();
	customerQueue->printQueue();

	for(int i = 0; i < NUM_TELLERS; i++){
		Teller *teller = tellers[i];
		teller->startWorking();
	}
	timer->startTimer(); // start the timer
	// Has 3 Elements:
	customerQueue->enqueue(new Customer(timer->readTimer()));
	customerQueue->enqueue(new Customer(timer->readTimer()));
	customerQueue->enqueue(new Customer(timer->readTimer()));
	usleep(100000);
	customerQueue->enqueue(new Customer(timer->readTimer()));

	while(timer->isRunning()){
		sched_yield();
	}

	// Close Bank:
	closeBank();

	/*
	while(true){
		int newCustomerEntryTime = ((rand()%(240-60))+60); // random # between 1 to 4 minutes in sim seconds
		printf("----> Adding customer in: %d\n", newCustomerEntryTime);

		usleep((int)( newCustomerEntryTime * SIMULATED_SEC_SCALE ));
		if(bankOpenSec > 0){
			// Add customer to queue!!
			Customer* c = new Customer(bankOpenSec);
			customerQueue->enqueue(c);
			//printf("^*^ Queue Size %d\n",customerQueue->size());
		}else{
			break;
		}
	}*/
	//closeBank();
}

/**
 * Close the bank
 */
void Bank::closeBank(){
	// Dismiss all Telemarketers:
	for(int i = 0; i < NUM_TELLERS; i++){
		Teller *teller = tellers[i];
		teller->stopWorking();
	}
	timer->stopTimer();

	printf("# ============================================ #\n");
	// Total Customers:
	printf("This fabulous bank has closed!\n");
	printf("# ============================================ #\n");
	printf("Customers Served:\t\t%d\n\n", metrics->getNumCustomers());
	printf("# -------------------------------------------- #\n");
	// Averages:
	printf("Average time in queue: \t\t%.2f\n", metrics->getAvgCustWaitTime());
	printf("Average service time is:\t%.2f\n", metrics->getAvgServiceTime());
	printf("Average teller wait time:\t%.2f\n\n", metrics->getAvgTellerWaitTime());
	printf("# -------------------------------------------- #\n");
	// Maximum Values:
	printf("Maximum time in queue: \t\t%d\n", metrics->getMaxCustWaitTime());
	printf("Maximum teller wait time:\t%d\n", metrics->getMaxTellerWaitTime());
	printf("Maximum time at teller:\t\t%d\n", metrics->getMaxServiceTime());
	printf("Maximum depth is:\t\t%d\n", metrics->getMaxDepth());
	printf("# -------------------------------------------- #\n");
}


Bank::~Bank() {
	// Delete the tellers
	for(int i = 0; i < NUM_TELLERS; i++){
		delete(tellers[i]);
	}

	// Delete the customer queue
	delete(customerQueue);
	delete(metrics);
}
