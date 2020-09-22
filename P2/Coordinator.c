#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "Coordinator.h"
const int EXPECTED_ARGUMENTS = 6;


int main(int argc, char *argv[]) {
	check_arg_count(argc);
	for(int x = 2; x < 6; x++){
		fork_function(argv[1], argv[x]);
	}
	printf("Coordinator: exiting.\n");
	return 0;
}

// Makes sure the proper number of arguments were passed in
void check_arg_count(int argc){
	if(argc != EXPECTED_ARGUMENTS){
		printf("Please enter 5 numbers. USAGE: ./coordinator 1 2 3 4 5\n");
                exit(1);
	}
}

void fork_function(char *divisor, char *dividend){
	pid_t pid = fork();
	// If pid is less than 0 the fork failed
        if(pid < 0){
                printf("Fork Failed\n");
                exit(-1);
        }
	// If pid = 0 theb its the child process and load in the checker program
        else if(pid == 0){
                execlp("./checker","checker.c",divisor,dividend, NULL);
        }
        else{
                printf("Coordinator: forked process with ID %d.\n", pid);
                printf("Coordinator: waiting for process [%d].\n", pid);
                int status;
		// Get return status of forked child
                if(waitpid(pid,&status,0)){
                        int result = WEXITSTATUS(status);
                        printf("Coordinator: child process %d returned %d.\n",pid,result);

                }
		// Again check if the child failed
                else{
                        printf("Child Failed\n");
			exit(-1);
                }
        }
}
