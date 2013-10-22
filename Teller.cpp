/*
 * Teller.cpp
 *
 *  Represents a Teller. Encapsulates a p-thread.
 *  Helps customers 
 *
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */

#include <time.h>
#include <customer.h>
#include <teller.h>

/**
* Constructor
* Sets the customer queue
*/
Teller::Teller(Queue* queue) {
	customerQueue = queue;
}

Teller::~Teller() {
	// TODO Auto-generated destructor stub
}


/**
 * Help customers waiting in the queue
 * Keeps helping customers until bank is closed AND there are no more customers
 * Each customer requires between 30 seconds and 7 minutes to complete their
 * transaction.
 */
void Teller::helpCustomers(){
	Customer customer;
	int timeReq;

	printf("Teller ready!");


	while(open || !customerQueue->empty()){
		customer = customerQueue->pop(); // get the next customer in the queue
		timeReq = (rand()%(420-30))+30; // random # b/w 30seconds and 7 minutes (in sec)
		sleep(timeReq); // help customer

		// should probably deallocate the customer eh?

	}
    done = true; // bank is closed and the customer queue is empty.

}


/**
 * Tell the teller to start working. Will initiate a thread representing the 
 * teller that will try to help customers.
 */
void Teller::startWorking() {
    open = true;
    done = false;
    int rc = pthread_create(&_thread, NULL, InternalThreadEntryFunc,this);

    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        return;
    }
}

/**
 * Stop working.
 * Will waiting until queue is empty, then quit by stopping thread.
 **/
void Teller::stopWorking() {
	open = false;
	printf("Bye bye\n");
   // while(!done){} // wait until customer queue is empty
    pthread_join(_thread,NULL);
}
