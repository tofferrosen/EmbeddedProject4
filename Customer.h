/*
 * Customer.h
 * Customer holds metrics about itself
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

class Customer {
public:
	Customer();
	Customer(int);
	virtual ~Customer();
	void setTellerTime(int);
	void setCustomerDone(int);
	int getWaitTime(void);
	int getServiceTime(void);
	int getBankEnterTime(void);
	
private:
	int bankEnterTime;
	int tellerServiceTime;
	int tellerDoneTime;
};

#endif /* CUSTOMER_H_ */
