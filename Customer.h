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
	Customer();
	virtual ~Customer();

private:
	int timeSpentInQeue;
	int timeWithTeller;
};

#endif /* CUSTOMER_H_ */
