/*
 * Customer.cpp
 * Customer holds metrics about itself
 *
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */

#include "Customer.h"

Customer::Customer(){

}
Customer::Customer(int curTime) {
	bankEnterTime = curTime;
}
void Customer::setTellerTime(int tTime){
	tellerServiceTime = tTime;
}

void Customer::setCustomerDone(int dTime){
	tellerDoneTime = dTime;
}

int Customer::getWaitTime(){
	return tellerServiceTime - bankEnterTime;
}

int Customer::getServiceTime(){
	return tellerDoneTime - tellerServiceTime;
}

Customer::~Customer() {}
