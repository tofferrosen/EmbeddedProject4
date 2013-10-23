/**
 * Queue
 * A thread safe queue.
 *
 * Wrapper around the std::deque with mutexes to ensure that only
 * one thread can modify the container (deque) at the time.
 */
#include <Queue.h>

/**
 * Fucntion: Constructor
 * Description: Initializes the mutex
 */
Queue::Queue() {
	pthread_mutex_init(&mutex, NULL);
}

/**
 * Function: Deconstructor
 * Description: Desctuctor
 */
Queue::~Queue() {
	// TODO Auto-generated destructor stub
}

/**
 * Function: pop()
 * Description: Pops and returns pointer to first element in the queue.
 * 				IF the queue is empty, returns null ptr.
 *
 * @threadsafe
 */
Customer * Queue::pop() {
	Customer *customer;

	pthread_mutex_lock(&mutex);
    // make sure the container is not empty
	if (container.empty()){
		customer = NULL;
	} else {
		customer = container.front();
		container.pop_front();
	}

	pthread_mutex_unlock(&mutex); 	// release mutex
	return customer;
}

/**
 * Function: printQueue()
 * Description: Prints the contents of the queue.
 * 				Used for *testing* purposes only.
 *
 * @threadsafe
 */
void Queue::printQueue() {
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
 * Function: empty()
 * Description: Checks if the queue is empty.
 *
 * @return bool true if queue is empty.
 * @threadsafe
 */
bool Queue::empty() {
	pthread_mutex_lock(&mutex);
	bool empty = false;
	empty = container.empty();
	pthread_mutex_unlock(&mutex);  // release mutex
	return empty;
}

/**
 * Function: enqueue()
 * Description: Enqueues a customer to the queue.
 * @param *customer: A ptr to the customer to be added.
 *
 * @threadsafe
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
 * Function: size()
 * Description: Checks the size of the queue.
 * @return int Size of the queue
 * @threadsafe
 **/
int Queue::size(){
	int size;
	pthread_mutex_lock(&mutex);
	size = container.size();
    pthread_mutex_unlock(&mutex);
    return size;
}

