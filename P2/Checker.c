#include "Checker.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	printf("Checker process [%d]: Starting.\n", getpid()); 
	int dividend = convert_char_to_int(argv[1]);
	int divisor = convert_char_to_int(argv[2]);
	return check_divisible(dividend, divisor, getpid());
}
// Arguments are passed in as chars and must be converted to an int
int convert_char_to_int(const char *argument){
	char *end;
	int value = strtol(argument, &end, 10);
        // Check to make sure a valid int was padded
	check_conversion_success(end, argument);
	return value;
}

void check_conversion_success(const char *end, const char *argument){
	if (end == argument || *end != '\0'){
                printf("Checker: Invalid input given- [%s], please enter only numbers\n", argument);
                //Number failed to convert return a failure, this turns out to be 255
		exit(-1);
        }
}

// If mod is 0 then the number is divisible
int check_divisible(int divisor, int number, int pid){
	if(number % divisor == 0){
		printf("Checker process [%d]: %d *IS* divisible by %d.\n",pid, number, divisor);
		printf("Checker process [%d]: Returning 1.\n", pid);
		return 1;
	}
	else{
		printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n",pid, number, divisor);
		printf("Checker process [%d]: Returning 0.\n", pid);
		return 0;
	}
}
