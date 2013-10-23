/*
 * Metrics.cpp
 *
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */

#include "Metrics.h"

void Metrics::addCustomer(Customer c){

	/*while(pthread_mutex_trylock(&mutex) != 0){
		usleep(1); // to not lock CPU
	}*/
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


void Metrics::addTellerWaitTime(int wt){
	printf("<WAIT_TIME=%d | MAX=%d| TOTAL=%d>",wt,maxTellerWait,totalTellerWait);
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

int Metrics::getNumCustomers(){
	return totalNumCustomers;
}// getNumCustomers()

int Metrics::getMaxDepth(){
	return maxWaitQueueSize;
}// getMaxDepth()
int Metrics::getTotalCustWaitTime(){
	return totalCustWaitTime;
}// getTotalCustWaitTime()

float Metrics::getAvgCustWaitTime(){
	return ((float)totalCustWaitTime)/((float)totalNumCustomers);
}// getAvgCustWaitTime()

int Metrics::getMaxCustWaitTime(){
	return maxCustWaitTime;
}// getMaxCustWaitTime()

float Metrics::getAvgServiceTime(){
	return (float)((totalServiceTime)/(totalNumCustomers));
}// getAvgServiceTime()

int Metrics::getMaxServiceTime(){
	return maxServiceTime;
}// getMaxServiceTime()

float Metrics::getAvgTellerWaitTime(){
	return (float)((totalTellerWait)/(NUM_TELLERS));
}// getAvgTellerWaitTime()

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
