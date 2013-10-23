/**
 * Queue
 * A thread safe queue.
 *
 * Wrapper around the std::deque with mutexes to ensure that only
 * one thread can modify the container (deque) at the time.
 */

#ifndef Project4_Queue_h
#define Project4_Queue_h

#include <pthread.h>
#include <deque>
#include <Customer.h>
#include <unistd.h>

using namespace std;

class Queue {
public:

	/**
	 * Function: Constructor
	 * Description: Initializes the mutex
	 */
    Queue();
    virtual ~Queue();
    
    /**
     * Function: pop()
     * Description: Pops and returns pointer to first element in the queue.
     * 				IF the queue is empty, returns null ptr.
     *
     * @threadsafe
     */
    Customer * pop();

    /**
     * Function: enqueue()
     * Description: Enqueues a customer to the queue.
     * @param *customer: A ptr to the customer to be added.
     *
     * @threadsafe
     */
    void enqueue(Customer *customer);

    /**
     * Function: empty()
     * Description: Checks if the queue is empty.
     *
     * @return bool true if queue is empty.
     * @threadsafe
     */
    bool empty();

    /**
     * Function: size()
     * Description: Checks the size of the queue.
     *
     * @return int Size of the queue
     * @threadsafe
     **/
    int size();

    /**
     * Function: printQueue()
     * Description: Prints the contents of the queue.
     * 				Used for *testing* purposes only.
     *
     * @threadsafe
     */
    void printQueue();
    
private:
    
    std::deque<Customer *> container; //contains customers
    pthread_mutex_t mutex;
    
};

#endif /* BLOCKINGQUEUE_H_ */

