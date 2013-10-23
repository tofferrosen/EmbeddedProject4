/*
 * Customer.cpp
 * Customer holds metrics about itself
 */

#include "Customer.h"

Customer::Customer(){}
Customer::Customer(int curTime) {
	bankEnterTime = curTime;
}

int Customer::getBankEnterTime(void){
	return bankEnterTime;
}
void Customer::setTellerTime(int tTime){
	tellerServiceTime = tTime;
}
void Customer::setCustomerDone(int dTime){
	tellerDoneTime = dTime;
}

int Customer::getWaitTime(){
	return bankEnterTime - tellerServiceTime ;
}

int Customer::getServiceTime(){
	return tellerServiceTime - tellerDoneTime ;
}

Customer::~Customer() {}
