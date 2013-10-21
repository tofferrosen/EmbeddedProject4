/*
 * Teller.h
 *
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */

#ifndef TELLER_H_
#define TELLER_H_

#include <vector>

class Teller {
public:
	Teller(Queue queue); // Constructor
	virtual ~Teller();
    
    void HelpCustomer();

private:
    int maxWaitTime; // max time waiting on a customer for metrics
    vector timesWithCustomers; // vector of times spent with customers metrics
    
};

#endif /* TELLER_H_ */
