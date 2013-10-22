//
//  Queue.h
//  Project4
//
//  Implements a thread safe queue based on the C++
//  double queue data structure with methdos of pop
//  and push_back
//
//  Created by Christoffer Rosen on 10/18/13.
//  Copyright (c) 2013 Christoffer Rosen. All rights reserved.
//

#ifndef Project4_Queue_h
#define Project4_Queue_h

#include <pthread.h>
#include <deque>
#include <Customer.h>
#include <unistd.h>

using namespace std;

class Queue {
public:
    Queue();
    virtual ~Queue();
    
    Customer * pop();
    void enqueue(Customer *customer);
    bool empty();
    
private:
    
    std::deque<Customer *> container; //contains customers
    pthread_mutex_t mutex;
    
};

#endif /* BLOCKINGQUEUE_H_ */

