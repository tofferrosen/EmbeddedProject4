/*
 * Metrics.cpp
 *
 * Object that captures all the metrics
 */

#include "Metrics.h"

/**
 * Function: addCustomer
 * Description: Add a customer every time it is finished
 * 				a transaction with a teller. Updates the
 * 				service time, wait time, and num of customers
 *
 * @param c	 A copy of a customer object.
 * @threadsafe
 */
void Metrics::addCustomer(Customer c){

	pthread_mutex_lock(&mutex);

	if( c.getWaitTime() > maxCustWaitTime ){
		maxCustWaitTime = c.getWaitTime();
	}
	if( c.getServiceTime() > maxServiceTime ){
		maxServiceTime = c.getServiceTime();
	}

	// Update Aggregate Wait Time:
	totalCustWaitTime += c.getWaitTime();

	// Update Aggregate Service Time:
	totalServiceTime += c.getServiceTime();
	totalNumCustomers++;

	// Release Mutex:
	pthread_mutex_unlock(&mutex);
}// addCustomer()

/**
 * Function: updateMaxDepth
 * Description: Updates the max depth of the queue.
 *
 * @param size int The current size of the queue.
 * @threadsafe
 */
void Metrics::updateMaxDepth(int size){
	while(pthread_mutex_trylock(&mutex) != 0){
		usleep(1); // to not lock CPU
	}
	if( maxWaitQueueSize < size ){
		maxWaitQueueSize = size;
	}

	// Release Mutex:
	pthread_mutex_unlock(&mutex);
}// updateMaxDepth()

/**
 * Function: addTellerWaitTime
 * Description: Adds the teller wait time. Updates the max and total teller wait tims
 *
 * @param wt The teller wait time.
 * @threadsafe
 */
void Metrics::addTellerWaitTime(int wt){

	while(pthread_mutex_trylock(&mutex) != 0){
		usleep(1); // to not lock CPU
	}
	if( wt > maxTellerWait ){
		maxTellerWait = wt;
	}

	totalTellerWait += wt;
	// Release Mutex:
	pthread_mutex_unlock(&mutex);
}// addTellerWaitTime()

/**
 * Function: getNumCustomers
 * Description: A getter for getting the totally number of customers.
 *
 * @return int the total number of customers seen.
 */
int Metrics::getNumCustomers(){
	return totalNumCustomers;
}// getNumCustomers()

/**
 * Function: getMaxDepth
 * Description: A getter for the max depth of the queue
 *
 * @return int max depth of the queue
 */
int Metrics::getMaxDepth(){
	return maxWaitQueueSize;
}// getMaxDepth()

/**
 * Function: getTotalCustWaitTIme
 * Description: A getter for the total customer wait time
 *
 * @return int total customer wait time of all customers seen.
 */
int Metrics::getTotalCustWaitTime(){
	return totalCustWaitTime;
}// getTotalCustWaitTime()

/**
 * Function: getAvgCustWaitTime
 * Description: A getter for the average customer wait time
 *
 * @return float the average customer wait time of all customers seen.
 */
float Metrics::getAvgCustWaitTime(){
	return ((float)totalCustWaitTime)/((float)totalNumCustomers);
}// getAvgCustWaitTime()

/**
 * Function: getMaxCustWaitTime
 * Description: A getter for the max cusomer wait time
 *
 * @return int the max customer wait time of all customers seen
 */
int Metrics::getMaxCustWaitTime(){
	return maxCustWaitTime;
}// getMaxCustWaitTime()

/**
 * Function: getAvgServiceTime
 * Description: A getter for the average service time for all customers.
 * 				This is the average time the customer is spent with the teller.
 *
 * @return float the average service time of all customers.
 */
float Metrics::getAvgServiceTime(){
	return (float)((totalServiceTime)/(totalNumCustomers));
}// getAvgServiceTime()

/**
 * Function: getMaxServiceTime
 * Description: A getter for the max service time for all customers.
 * 				This is the most time a customer spent with a teller.
 *
 * @return int the max time a customer spent with a teller
 */
int Metrics::getMaxServiceTime(){
	return maxServiceTime;
}// getMaxServiceTime()

/**
 * Function: getAvgTellerWaitTime
 * Description: Getter for the average teller wait time
 *
 * @return float the average teller wait time.
 */
float Metrics::getAvgTellerWaitTime(){
	return (float)((totalTellerWait)/(NUM_TELLERS));
}// getAvgTellerWaitTime()


/**
 * Function: getMaxTellerWaitTime
 * Description: A getter for the max teller wait time
 *
 * @return int the max teller wait time.
 */
int Metrics::getMaxTellerWaitTime(){
	return maxTellerWait;
}// getMaxTellerWaitTime()



Metrics::Metrics() {
	pthread_mutex_init(&mutex, NULL);
	totalCustWaitTime = 0;
	maxCustWaitTime = 0;

	totalServiceTime = 0;
	maxServiceTime = 0;

	totalTellerWait = 0;
	maxTellerWait = 0;
	
	totalNumCustomers = 0;
	maxWaitQueueSize = 0;
}

Metrics::~Metrics() {
	// TODO Auto-generated destructor stub
}
