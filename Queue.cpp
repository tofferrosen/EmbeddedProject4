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
	// Initialize Mutex:
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

    // acquire lock mutex
    /*while(pthread_mutex_trylock(&mutex) != 0){
    	sched_yield(); // to not lock CPU
    }*/
	pthread_mutex_lock(&mutex);
    // make sure the container is not empty
	if (container.empty()){
		customer = NULL;
	} else {
		customer = container.front();
		//printf("                       pop from the queue\n");
		//printf("                       Size is now: %d\n", container.size());
		container.pop_front();
	}

	pthread_mutex_unlock(&mutex); 	// release mutex
	return customer;
}

void Queue::printQueue() {
	// aquire lock mutex
	/*while(pthread_mutex_trylock(&mutex) != 0){
		sched_yield(); // to not lock CPU
	}*/
	pthread_mutex_lock(&mutex);
	printf("Queue: ");
	for(unsigned int i = 0; i < container.size(); i++){
		Customer* c = container.at(i);
		printf("%d ",c->getBankEnterTime());
	}
	printf("\n");
	pthread_mutex_unlock(&mutex);  // release mutex
}
/**
 * Returns true if queue is empty
 */
bool Queue::empty() {
	// aquire lock mutex
	/*while(pthread_mutex_trylock(&mutex) != 0){
		sched_yield(); // to not lock CPU
	}*/
	pthread_mutex_lock(&mutex);
	bool empty = false;
	empty = container.empty();
	pthread_mutex_unlock(&mutex);  // release mutex
	return empty;
}

/**
 * Adds customer to the end of the queue.
 */
void Queue::enqueue(Customer *customer){

	// aquire lock mutex
	/*while(pthread_mutex_trylock(&mutex) != 0){
		usleep(1); // to not lock CPU
	}*/

	pthread_mutex_lock(&mutex);
	//printf("A new customer has entered!\n");
    container.push_back(customer);
    pthread_mutex_unlock(&mutex);
}

/**
 * Get size of the container
 **/
int Queue::size(){
	// aquire lock mutex
	int size;
	/*while(pthread_mutex_trylock(&mutex) != 0){
		sched_yield(); // to not lock CPU
	}*/
	pthread_mutex_lock(&mutex);
	size = container.size();
    pthread_mutex_unlock(&mutex);
    return size;
}

