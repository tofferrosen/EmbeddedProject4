/**
 * TimerSys.h
 *
 * This class represents the system timer.
 * Encapsulates a timer thread.
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "Constants.h"

#ifndef TIMERSYS_H_
#define TIMERSYS_H_

class TimerSys{
public:
	/**
	 * Function: Constructor
	 * Description: Initalizes the timer.
	 *
	 * @param duration: The total duration of the timer, the point it starts decrementing.
	 * @param sim_spped: The simulation speed.
	 */
	TimerSys( int duration, float sim_speed );
	virtual ~TimerSys(void);

	/**
	 * Function: readTimer()
	 * Description: Reads the current time of the timer
	 *
	 * @return int current value of the timer
	 */
	int readTimer(void);

	/**
	 * Function: isRunning()
	 * Description: Checks whether the timer is still running
	 *
	 * @return bool true if timer is still running
	 */
	bool isRunning(void);

	/**
	 * Function: startTimer()
	 * Description: Starts the timer and creats the thread.
	 */
	void startTimer(void);

	/**
	 * Function: timerDecrementer()
	 * Description: Decrements the timer. This is the function passed into
	 * 				the thread. Stops when timer is shut off.
	 */
	void timerDecrementer();

	/**
	 * Function: stopTimer()
	 * Description: Stops the timer and cleans the timer thread.
	 */
	void stopTimer(void);
private:
	static void * TimerThreadFunc(void * This) {((TimerSys *)This)->timerDecrementer(); return NULL;};
	bool timerOn;
	pthread_t thread;
	pthread_mutex_t mutex;
	int timerVal;
	float speed;
	bool inRunMode;
};

#endif /* TIMERSYS_H_ */
