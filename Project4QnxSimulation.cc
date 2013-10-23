#include <cstdlib>
#include <iostream>
#include <Constants.h>
#include <Bank.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
	Bank *bank = new Bank();

	clock_t t = clock();
	bank->openAndRunBank();
	delete(bank);
	t = clock()-t;

	printf("Execution Time: %d %f seconds.\n",t,((float)t)/CLOCKS_PER_SEC);
	return EXIT_SUCCESS;
}
