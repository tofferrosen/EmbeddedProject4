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

Customer Queue::pop() {

    // lock mutex
    pthread_mutex_lock(&mutex);
    
    if (container.empty()){
        // TODO
    }
    Customer customer = container.front();
    container.pop_front();

    // release mutex
    pthread_mutex_unlock(&mutex);
    return customer;
}

bool Queue::empty() {
	bool empty = false;
	pthread_mutex_lock(&mutex);
	empty = container.empty();
	pthread_mutex_unlock(&mutex);
	return empty;
}

void Queue::enqueue(Customer *customer){
    pthread_mutex_lock(&mutex);
    container.push_back(*customer);
    pthread_mutex_unlock(&mutex);
    
}
