/**
 * Teller.h
 *
 * The Teller object services customers--serves as a thread-safe
 * wrapper for removing objects from the customer queue.
 *
 * Created on: Oct 16, 2013
 * Author: cbr4830, lgs8331
 */

#ifndef TELLER_H_
#define TELLER_H_

#include <vector>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <queue.h>
#include <unistd.h>
#include <time.h>

#include "Constants.h"
#include "Customer.h"
#include "TimerSys.h"

class Teller {
public:
	/**
	 * Function:	Constructor
	 * Description:	Initializes the teller object to be capable of handling customers.
	 * 				The teller also has a reference to the system time and uses it to
	 * 				handle time-related events in the system.
	 */
	Teller(Queue* queue, int tellerNumber, TimerSys* t); // Constructor

	/**
	 * Function:	Destructor
	 * Description:	Called when the class is being destroyed/discarded.
	 */
	virtual ~Teller();

	/**
	 * Function:	startWorking
	 * Description:	Tell the teller to start working. Will initiate a thread
	 * 				representing the teller that will try to help customers.
	 */
    void startWorking();

    /**
     * Function:	stopWorking
     * Description:	Will waiting until queue is empty, then quit by stopping thread.
     **/
    void stopWorking();

    
protected:
	/**
	 * Function:	helpCustomers
	 * Description:	Help customers waiting in the queue Keeps helping customers
	 * 				until bank is closed AND there are no more customers Each
	 * 				customer requires between 30 seconds and 7 minutes to
	 * 				complete their transaction.
	 */
    void helpCustomers();

private:
    static void * TellerRunFunction(void * This) {((Teller *)This)->helpCustomers(); return NULL;}
    pthread_t thread;
    Queue *customerQueue;
    bool open;
    bool done;
    int tellerNum;
    TimerSys* timer;
};

#endif /* TELLER_H_ */
