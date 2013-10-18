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

class Teller {
    
public:
    void startWorking();
    void stopWorking();
    
private:
    static void * InternalThreadEntryFunc(void * This) {((Teller *)This)->helpCustomers(); return NULL;}
    pthread_t _thread;
    
protected:
    void helpCustomers();
};


/**
 * Help customers waiting in the queue
 */
void Teller::helpCustomers(){
    
    while(true){
        // TODO
    }
}

/**
 * Tell the teller to start working. Will initiate a thread representing the 
 * teller that will try to help customers.
 */
void Teller::startWorking() {
    
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
    
    // TODO make sure queue is empty.
    pthread_exit(_thread);
}