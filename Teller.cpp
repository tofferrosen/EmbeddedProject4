/*
 * Teller.cpp
 *
 *  Represents a Teller. Encapsulates a p-thread.
 *  Helps customers 
 *
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */


#include <Teller.h>

/**
* Constructor
* Sets the customer queue
*/
Teller::Teller(Queue* queue, int tellerNumber) {
	customerQueue = queue;
	tellerNum = tellerNumber;
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
	Customer *customer;
	int timeReq;

	//printf("Teller ready!");

	while(open || !customerQueue->empty()){
		customer = customerQueue->pop(); // get the next customer in the queue
		// queue was empty
		if(customer == NULL){
			usleep(10);
		} else {
			//printf("  Teller %d is helping a customer\n",tellerNum);
			timeReq = (rand()%(420-30))+30; // random # b/w 30seconds and 7 minutes (in sec)
			//printf("<----- helping customer for: %d\n", timeReq);
			usleep((int)(timeReq*SIMULATED_SEC_SCALE)); // help customer
			metrics->addCustomer(*customer);
			delete(customer); // done!
		}
	}
    done = true; // bank is closed and the customer queue is empty.
    //printf("Teller %d is finished\n", tellerNum);

}

/**
 * Tell the teller to start working. Will initiate a thread representing the 
 * teller that will try to help customers.
 */
void Teller::startWorking() {
    open = true;
    done = false;
    int rc = pthread_create(&thread, NULL, TellerRunFunction,this);

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
	//printf("  Teller %d is finishing\n", tellerNum);
    while(!done){usleep(10);} // wait until customer queue is empty
    pthread_join(thread,NULL);
}
