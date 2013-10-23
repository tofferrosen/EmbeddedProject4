/**
 * Constants.h
 *
 * Created on: Oct 22, 2013
 * Author: cbr4830
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// Seven hours in seconds:
const int WORK_DAY = 1300;//25200;

// One second in microseconds:
const float ONE_SECOND = 1000000;

// The time scaler, used to adjust simulation speed:
const float TIME_SCALE = 0.01;
const int TIME_INCR = 30;
const int NUM_TELLERS = 3;
// Speed calculation:
const int DEFAULT_SPEED = (int)(ONE_SECOND*TIME_SCALE);

#endif /* CONSTANTS_H_ */
