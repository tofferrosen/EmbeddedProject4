/*
 * Customer.h
 *
 *	Customer holds metrics about itself
 *	Customer
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

class Customer {
public:
	Customer(int);
	virtual ~Customer();
	setTellerTime(int);
	setCustomerDone(int);

private:
	int bankEnterTime;
	int tellerServiceTime;
	int tellerDoneTime;
};

#endif /* CUSTOMER_H_ */
