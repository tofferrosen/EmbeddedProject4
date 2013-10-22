#include <cstdlib>
#include <iostream>
#include <Bank.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("#Code Start# \n");
	Bank *bank = new Bank();
	bank->openAndRunBank();

	delete(bank);
	printf("\nCode done!");
	return EXIT_SUCCESS;
}
