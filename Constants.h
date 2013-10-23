/*
 * Constants.h
 *
 *  Created on: Oct 22, 2013
 *      Author: cbr4830
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

const int SEVEN_HOUR_IN_SECONDS = 25200;

// 100 ms per minute --> 100ms = 100000us
const int SIMULATED_MIN_SCALE = 100;
const int SIMULATED_SEC_SCALE = (int)(SIMULATED_MIN_SCALE / 60);

static int bankOpenSec = SEVEN_HOUR_IN_SECONDS;

#endif /* CONSTANTS_H_ */
