/*
 * Teller.h
 *
 *  Created on: Oct 16, 2013
 *      Author: cbr4830
 */

#ifndef TELLER_H_
#define TELLER_H_

#include <vector>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <queue.h>
#include <unistd.h>


class Teller {
public:
	Teller(Queue* queue, int tellerNumber); // Constructor
	virtual ~Teller();
    void startWorking();
    void stopWorking();

    
protected:
    void helpCustomers();

private:
    static void * TellerRunFunction(void * This) {((Teller *)This)->helpCustomers(); return NULL;}
    pthread_t thread;
    Queue *customerQueue;
    bool open;
    bool done;
    int tellerNum;
    
};

#endif /* TELLER_H_ */
