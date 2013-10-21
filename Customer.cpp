/*
 * Customer.cpp
 * Customer holds metrics about itself
 *
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */

#include "Customer.h"

Customer::Customer(int curTime) {
	bankEnterTime = curTime;
}
Customer::setTellerTime(int tTime){
	tellerServiceTime = tTime;
}

Customer::setCustomerDone(int dTime){
	tellerDoneTime = dTime;
}


Customer::~Customer() {}
