/**
 * Teller.cpp
 *
 * Represents a Teller. Encapsulates a p-thread.
 * Services customers that enter the system.
 *
 * Created on: Oct 16, 2013
 * Author: cbr4830, lgs8331
 */

#include <Teller.h>

/**
 * Function:	Constructor
 * Description:	Initializes the teller object to be capable of handling customers.
 * 				The teller also has a reference to the system time and uses it to
 * 				handle time-related events in the system.
 */
Teller::Teller(Queue* queue, int tellerNumber,TimerSys* t) {
	customerQueue = queue;
	tellerNum = tellerNumber;
	timer = t;
}// Teller()

/**
 * Function:	Destructor
 * Description:	Called when the class is being destroyed/discarded.
 */
Teller::~Teller() {/* Unused */}

/**
 * Function:	helpCustomers
 * Description:	Help customers waiting in the queue Keeps helping customers
 * 				until bank is closed AND there are no more customers Each
 * 				customer requires between 30 seconds and 7 minutes to
 * 				complete their transaction.
 */
void Teller::helpCustomers(){
	Customer *customer;
	int timeReq, waitTimer = -1;

	while( open || !customerQueue->empty() ){
		int curTime;

		// Update Maximum Queue Depth:
		metrics->updateMaxDepth(customerQueue->size());
		if( waitTimer == -1 ){
			waitTimer = timer->readTimer();
		}
		customer = customerQueue->pop(); // get the next customer in the queue

		// queue was empty
		if( customer == NULL ){
			sched_yield();
		}else{
			//timeReq = (rand()%(420-30))+30; // random # b/w 30seconds and 7 minutes (in sec)
			timeReq = 5; // Five Simulation Seconds;

			metrics->addTellerWaitTime( waitTimer - (timer->readTimer()) );

			curTime = timer->readTimer();
			customer->setTellerTime(curTime);
			customer->setCustomerDone(curTime - (timeReq*TIME_INCR));

			printf("Teller #%d: Begin Servicing Customer(@%d.).\n",tellerNum,curTime);
			while(timer->readTimer() > (curTime-timeReq*TIME_INCR)){
				usleep(10);
				sched_yield();
			}
			metrics->addCustomer(*customer);
			printf("Teller #%d: Completed Servicing Customer (%d)(%d).\n",tellerNum,customer->getWaitTime(),customer->getServiceTime());
			// Log Customer Data in Aggregator:
			waitTimer = -1;
			delete(customer);
		}
	}
	// When Bank is closed & Queue is Empty:
    done = true;
}// helpCustomers()

/**
 * Function:	startWorking
 * Description:	Tell the teller to start working. Will initiate a thread
 * 				representing the teller that will try to help customers.
 */
void Teller::startWorking() {
	open = true;done = false;
	printf("Teller #%d punched into work.\n", tellerNum);
	int rc = pthread_create(&thread, NULL, TellerRunFunction,this);
	rc = pthread_setname_np(thread, "Teller #"+tellerNum);
	sched_yield();
	if (rc){
		fprintf(stderr, "ERROR(%d): PThread not created.\n", rc);
		return;
	}
}// startWorking()

/**
 * Function:	stopWorking
 * Description:	Will waiting until queue is empty, then quit by stopping thread.
 **/
void Teller::stopWorking() {
	open = false;
	printf("  Teller %d is finishing\n", tellerNum);
    while(!done){sched_yield();} // wait until customer queue is empty
    pthread_join(thread,NULL);
}// stopWorking()
