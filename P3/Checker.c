#include "Checker.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
	int dividend = convert_char_to_int(argv[1]);
	int divisor = convert_char_to_int(argv[2]);
	int shmID = convert_char_to_int(argv[3]);
	int var;
        read(shmID, &var, sizeof(int));
	
	struct check check_process = { .dividend = dividend, .divisor = divisor, .shmID = var,
		 .pid = getpid(), .divisible = 0, .print_string = "IS NOT"};
	print_start_info(&check_process);

	void *ptr = shmat(check_process.shmID, NULL, 0);
	check_divisible(&check_process);
	*(int*)ptr = check_process.divisible;
	
	printf("Checker Process [%d]: wrote result (%d) to shared memory.\n", check_process.pid, check_process.divisible);
	shmdt(ptr);
	return 1;
}

int convert_char_to_int(const char *argument){
	char *end;
	int value = strtol(argument, &end, 10);
	check_conversion_success(end, argument);
	return value;
}

void check_conversion_success(const char *end, const char *argument){
	if (end == argument || *end != '\0'){
                printf("Checker: Invalid input given- [%s], please enter only numbers\n", argument);
		exit(-1);
        }
}

void print_start_info(struct check *divisible){
	printf("Checker process [%d]: Starting.\n", divisible->pid);
        printf("Checker process [%d] : read %lu bytes containing shm ID %d.\n", divisible->pid, sizeof(divisible->shmID), divisible->shmID);

}

int check_divisible(struct check *divisible){
	if(divisible->dividend % divisible->divisor == 0){
		divisible->divisible = 1;
		strcpy(divisible->print_string, "IS");
	}
	print_results(divisible);	
	
	return divisible->divisible;
}

void print_results(struct check *divisible){
	printf("Checker process [%d]: %d *%s* divisible by %d.\n",divisible->pid,divisible->dividend,divisible->print_string,divisible->divisor);
        printf("Checker process [%d]: Returning %d.\n", divisible->pid, divisible->divisible);
}
