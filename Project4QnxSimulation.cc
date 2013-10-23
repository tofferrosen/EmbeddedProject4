/**
 * Project4QnxSimulation.cc
 *
 * The main entry point for the algorithm.
 *
 * Created on: Oct 16, 2013
 * Author: cbr4830, lgs8331
 */
// Standard Library Headers:
#include <cstdlib>
#include <stdio.h>
#include <time.h>

// Metrics Object:
#include "Metrics.h"
Metrics* metrics;

// Custom Headers:
#include "Constants.h"
#include "TimerSys.h"
#include "Bank.h"

/**
 * Function:	main
 * Description:	The main entry point for the program.
 */
int main(int argc, char *argv[]) {
	// Declare System Timer:
	TimerSys* timer = new TimerSys( WORK_DAY, DEFAULT_SPEED );

	// Declare Metrics Aggregator:
	metrics = new Metrics();

	// Create & Open Bank:
	Bank *bank = new Bank(timer);
	bank->openAndRunBank();

	// Destroy Pointers:
	delete(bank);
	delete(timer);

	// Exit Program:
	return EXIT_SUCCESS;
}// main()
