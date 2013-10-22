/*
 * Metrics.cpp
 *
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */

#include "Metrics.h"

void Metrics::addCustomer(Customer c){
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
}// addCustomer()

void Metrics::updateMaxDepth(int size){
	if( maxWaitQueueSize < size ){
		maxWaitQueueSize = size;
	}
}// updateMaxDepth()


void Metrics::addTellerWaitTime(int wt){
	if( wt > maxWaitQueueSize ){
		maxWaitQueueSize = wt;
	}

	totalTellerWait += wt;
}// addTellerWaitTime()

float Metrics::getAvgCustWaitTime(){
	return ((float)totalCustWaitTime)/((float)totalNumCustomers);
}// getAvgQueueWaitTime()

float Metrics::getAvgServiceTime(){
	return ((float)totalServiceTime)/((float)totalNumCustomers);
}// getAvgQueueWaitTime()

int Metrics::getNumCustomers(){
	return totalNumCustomers;
}// getNumCustomers()

Metrics::Metrics() {
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
