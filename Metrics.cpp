/*
 * Metrics.cpp
 *
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */
#include <pthread.h>
#include <unistd.h>
#include "Metrics.h"
#include <stdio.h>

void Metrics::addCustomer(Customer c){
	printf("Trying to aquire lock\n");
	while(pthread_mutex_trylock(&mutex) != 0){
		usleep(1); // to not lock CPU
	}
	printf("lock aquired\n");
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
	printf("mutex unlocked\n");
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
	while(pthread_mutex_trylock(&mutex) != 0){
		usleep(1); // to not lock CPU
	}
	if( wt > maxWaitQueueSize ){
		maxWaitQueueSize = wt;
	}

	totalTellerWait += wt;
	// Release Mutex:
	pthread_mutex_unlock(&mutex);
}// addTellerWaitTime()

int Metrics::getNumCustomers(){
	return totalNumCustomers;
}// getNumCustomers()

int Metrics::getMaxDepth(){
	return -1;
}// getMaxDepth()

float Metrics::getAvgCustWaitTime(){
	return ((float)totalCustWaitTime)/((float)totalNumCustomers);
}// getAvgCustWaitTime()

int Metrics::getMaxCustWaitTime(){
	return -1;
}// getMaxCustWaitTime()

float Metrics::getAvgServiceTime(){
	return ((float)totalServiceTime)/((float)totalNumCustomers);
}// getAvgServiceTime()

int Metrics::getMaxServiceTime(){
	return -1;
}// getMaxServiceTime()

float Metrics::getAvgTellerWaitTime(){
	return -1;
}// getAvgTellerWaitTime()

int Metrics::getMaxTellerWaitTime(){
	return -1;
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
