/*
 * Metrics.cpp
 *
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */

#include "Metrics.h"

Metrics::addCustomer( Customer c ){
	if( c.getWaitTime() > maxCustWaitTime ){
		maxCustWaitTime = c.getWaitTime();
	}
	if( c.getServiceTime() > maxServiceTime ){
		maxServiceTime = c.getServiceTime();
}

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
