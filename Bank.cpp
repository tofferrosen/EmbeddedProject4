/**
 * Bank.cpp
 *
 * Represents the bank
 *
 * Starts and stops the tellers, and while the bank is open
 * constantly adds customers every 1 to 4 minutes.
 */

#include "Bank.h"

/**
 * Function: Constructor
 * Description: Instantiates the customer queue and tellers.
 *
 * @param t A ptr to the system timer.
 */
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
 * Function: openAndRunBank()
 * Description: Opens the bank, starts running the global timer, and
 * 				adds customers to queue while bank is open. When bank is
 * 				operating hours end, closes the bank.
 */
void Bank::openAndRunBank(){
	printf("This #Fabulous bank has opened!\n\n");

	for(int i = 0; i < NUM_TELLERS; i++){
		Teller *teller = tellers[i];
		teller->startWorking();
	}
	// Start the timer
	timer->startTimer();

	while(timer->isRunning()){
		int newCustomerEntryTime = (((rand()%(240-60))+60)/30);
		int curTime = timer->readTimer();

		while(timer->readTimer() > (curTime-newCustomerEntryTime*TIME_INCR)){
			usleep(10);
			sched_yield();
		}
		customerQueue->enqueue(new Customer(timer->readTimer()));
	}

	// Close Bank:
	closeBank();
}

/**
 * Function: closeBank()
 * Description: Closes the bank by first telling the tellers to finish the remaining
 * 				customers in the queue and clean themselves up. Then, it stops the timer.
 */
void Bank::closeBank(){
	// Dismiss all tellers
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

/**
 * Function: Destructor
 * Description: Deletes the tellers and the customer queue and the metrics object upon desctruction.
 */
Bank::~Bank() {
	// Delete the tellers
	for(int i = 0; i < NUM_TELLERS; i++){
		delete(tellers[i]);
	}

	// Delete the customer queue
	delete(customerQueue);
	delete(metrics);
}
