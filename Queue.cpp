//
//  Queue.cpp
//  Project4
//
//	Thread safe queue by requiring a mutex in order to read or write to it.
//
//  Created by Christoffer Rosen on 10/18/13.
//  Copyright (c) 2013 Christoffer Rosen. All rights reserved.
//

#include <Queue.h>

Queue::Queue() {
	// initalize the mutex!
	pthread_mutex_init(&mutex, NULL);
}

Queue::~Queue() {
	// TODO Auto-generated destructor stub
}

/**
 * Pops and returns pointer to first element in the queue.
 * IF the queue is empty, returns null ptr.
 */
Customer * Queue::pop() {
	Customer *customer;

    // aquire lock mutex
    while(pthread_mutex_trylock(&mutex) != 0){
    	usleep(100); // to not lock CPU
    }

    // make sure the container is not empty
	if (container.empty()){
		customer = NULL;
	} else {
		customer = container.front();
		printf("                       pop from the queue\n");
		printf("                       Size is now: %d\n", container.size());
		container.pop_front();
	}

	pthread_mutex_unlock(&mutex); 	// release mutex
	return customer;
}

/**
 * Returns true if queue is empty
 */
bool Queue::empty() {
	bool empty = false;
	// aquire lock mutex
	while(pthread_mutex_trylock(&mutex) != 0){
		usleep(100); // to not lock CPU
	}
	empty = container.empty();
	pthread_mutex_unlock(&mutex);  // release mutex
	return empty;
}

/**
 * Adds customer to the end of the queue.
 */
void Queue::enqueue(Customer *customer){

	// aquire lock mutex
	while(pthread_mutex_trylock(&mutex) != 0){
		usleep(100); // to not lock CPU
	}
	printf("A new customer has entered!\n");
    container.push_back(customer);
    pthread_mutex_unlock(&mutex);
}
