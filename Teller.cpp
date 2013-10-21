/*
 * Teller.cpp
 *
 *  Represents a Teller. Encapsualtes a p-thread.
 *  Helps customers 
 *
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

class Teller {
    
public:
    void startWorking();
    void stopWorking();
    
private:
    static void * InternalThreadEntryFunc(void * This) {((Teller *)This)->helpCustomers(); return NULL;}
    pthread_t _thread;
    Queue customerQueue;
    bool open;
    bool done;
    
protected:
    void helpCustomers();
};


/**
 * Help customers waiting in the queue
 * Keeps helping customers until bank is closed AND there are no more customers
 * Each customer requires between 30 seconds and 7 minutes to complete their
 * transaction.
 */
void Teller::helpCustomers(){
	time_t timer;
	Customer customer;
	int timeReq;
	double currentTime;
	double timeToWait;
	struct tm y2k;

	y2k.tm_hour = 0; y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

    while(open || !customerQueue.empty()){

    	customer = customerQueue.pop(); // get the next customer in the queue
    	timeReq = rand() % 30 + 420; // random # between 30 and 7 minutes
    	time(&timer); // get current time
    	currentTime = difftime(timer,mktime(&y2k)); // seconds since y2k
    	timeToWait = currentTime + timeReq; // seconds + random time between 30 and 7 minutes

    	// helping customer...
    	while(currentTime < timeToWait){
    		time(&time);
    		currentTime = difftime(timer,mktime(&y2k));
    	}
    }

    done = true; // bank is closed and the customer queue is empty.
}

/**
 * Constructor
 * Sets the customer queue
 */
Teller::Teller(Queue queue) {
	customerQueue = queue;
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

    while(!done){} // wait until customer queue is empty
    pthread_exit(_thread);
}
