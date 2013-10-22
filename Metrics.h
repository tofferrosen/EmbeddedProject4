/*
 * Metrics.h
 *
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */

#ifndef METRICS_H_
#define METRICS_H_
#include "Customer.h"

class Metrics {
public:
	Metrics();
	virtual ~Metrics();
	void addCustomer( Customer c ); // Add everytime customer is finished
		// update total wait, ;
		// update max wait, service time;
		// update max depth;

	void addTellerWaitTime( int wt ); // Add everytime a customer comes in

	float getAvgQueueWaitTime();
	float getAvgServiceTime(); // average time with teller
	float getNumCustomers();

private:
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
