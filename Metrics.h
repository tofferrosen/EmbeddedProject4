/*
 * Metrics.h
 *
 * Object that captures all the metrics statistics
 */

#ifndef METRICS_H_
#define METRICS_H_
#include <pthread.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "Constants.h"
#include "Customer.h"

class Metrics {
public:
	Metrics();
	virtual ~Metrics();

	/**
	 * Function: addCustomer
	 * Description: Add a customer every time it is finished
	 * 				a transaction with a teller. Updates the
	 * 				service time, wait time, and num of customers
	 *
	 * @param c	 A copy of a customer object.
	 * @threadsafe
	 */
	void addCustomer(Customer c);

	/**
	 * Function: updateMaxDepth
	 * Description: Updates the max depth of the queue.
	 *
	 * @param size int The current size of the queue.
	 * @threadsafe
	 */
	void updateMaxDepth(int size);

	/**
	 * Function: addTellerWaitTime
	 * Description: Adds the teller wait time. Updates the max and total teller wait tims
	 *
	 * @param wt The teller wait time.
	 * @threadsafe
	 */
	void addTellerWaitTime(int wt); // Add everytime a customer comes in

	/**
	 * Function: getNumCustomers
	 * Description: A getter for getting the totally number of customers.
	 *
	 * @return int the total number of customers seen.
	 */
	int getNumCustomers();

	/**
	 * Function: getMaxDepth
	 * Description: A getter for the max depth of the queue
	 *
	 * @return int max depth of the queue
	 */
	int getMaxDepth();

	/**
	 * Function: getAvgCustWaitTime
	 * Description: A getter for the average customer wait time
	 *
	 * @return float the average customer wait time of all customers seen.
	 */
	float getAvgCustWaitTime();

	/**
	 * Function: getMaxCustWaitTime
	 * Description: A getter for the max cusomer wait time
	 *
	 * @return int the max customer wait time of all customers seen
	 */
	int getMaxCustWaitTime();

	/**
	 * Function: getAvgServiceTime
	 * Description: Returns the average service time for all customers.
	 * 				This is the average time the customer is spent with the teller.
	 *
	 * @return float the average service time of all customers.
	 */
	float getAvgServiceTime();

	/**
	 * Function: getMaxServiceTime
	 * Description: A getter for the max service time for all customers.
	 * 				This is the most time a customer spent with a teller.
	 *
	 * @return int the max time a customer spent with a teller
	 */
	int getMaxServiceTime();

	/**
	 * Function: getAvgTellerWaitTime
	 * Description: Getter for the average teller wait time
	 *
	 * @return float the average teller wait time.
	 */
	float getAvgTellerWaitTime();

	/**
	 * Function: getMaxTellerWaitTime
	 * Description: A getter for the max teller wait time
	 *
	 * @return int the max teller wait time.
	 */
	int getMaxTellerWaitTime();

	/**
	 * Function: getTotalCustWaitTIme
	 * Description: A getter for the total customer wait time
	 *
	 * @return int total customer wait time of all customers seen.
	 */
	int getTotalCustWaitTime();
private:
	pthread_mutex_t mutex;
	int totalCustWaitTime;
	int maxCustWaitTime;

	int totalServiceTime;
	int maxServiceTime;

	int totalTellerWait;
	int maxTellerWait;
	
	int totalNumCustomers;
	int maxWaitQueueSize;
};

#endif /* METRICS_H_ */
