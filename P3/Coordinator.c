#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "Coordinator.h"
const int EXPECTED_ARGUMENTS = 6;
const int NUMBER_OF_PROCESSES = 4;


int main(int argc, char *argv[]) {
	check_arg_count(argc);
	int shared_mem_ids[NUMBER_OF_PROCESSES];
	create_shared_mem_id(shared_mem_ids, NUMBER_OF_PROCESSES);
	
	// Array of pointers to struct is too hard
	struct process allProcessesArray[NUMBER_OF_PROCESSES];
	
	for(int i = 0; i < NUMBER_OF_PROCESSES; i++){
		struct process parentProcess = { .dividend = argv[1], .divisor = argv[i+2], .shmID = shared_mem_ids[i] };
		if(pipe(parentProcess.fd) < 0){
			printf("Pipe Failed\n");
			exit(1);
		}
		fork_function(&parentProcess);
		allProcessesArray[i] = parentProcess;
	}
	for(int i = 0; i < NUMBER_OF_PROCESSES; i++){
		printf("Coordinator: waiting on child process ID %d...\n", allProcessesArray[i].pid);
		void *ptr = shmat(shared_mem_ids[i], NULL, SHM_RDONLY);
		int status;
		waitpid(allProcessesArray[i].pid, &status, 0);
		if(status){
			int result = *(int*)ptr;
			if(result){
				printf("Coordinator: result %d read from shared Memory: %s is divisible by %s.\n", result, allProcessesArray[i].divisor, allProcessesArray[i].dividend);		
			}
			else{
				printf("Coordinator: result %d read from shared Memory: %s is not divisible by %s.\n", result, allProcessesArray[i].divisor, allProcessesArray[i].dividend);	
			}
		}

	}
	delete_shared_mem_id(shared_mem_ids, NUMBER_OF_PROCESSES);
	printf("Coordinator: exiting.\n");
	return 0;
}

void check_arg_count(int argc){
	if(argc != EXPECTED_ARGUMENTS){
		printf("Please enter 5 numbers. USAGE: ./coordinator 1 2 3 4 5\n");
                exit(1);
	}
}

void create_shared_mem_id(int *shared_mem_ids, int sizeOfArray){
	for(int i = 0; i < sizeOfArray; i++){
		shared_mem_ids[i] = shmget(IPC_PRIVATE, sizeof(int), IPC_PRIVATE | 0664);
	}
}

void delete_shared_mem_id(int *shared_mem_ids, int sizeOfArray){
	for(int i = 0; i < sizeOfArray; i++){
		shmctl(shared_mem_ids[i], IPC_RMID, 0);
	} 
}

void fork_function(struct process *processInfo){
	pid_t pid = fork();
        if(pid < 0){
                printf("Fork Failed\n");
                exit(-1);
        }
        else if(pid > 0){
		processInfo->pid = pid;
		forked_Parent(processInfo);
	}
	else if(pid == 0){
                char str[8];
                forked_Child(processInfo, str);
		execlp("./checker","checker.c",processInfo->divisor,processInfo->dividend,str, NULL);
        }
}

void forked_Parent(struct process *parentProcess){
	printf("Coordinator: forked process with ID %d.\n", parentProcess->pid);
	parent_CloseandWrite(parentProcess);
	printf("Coordinator: wrote shm ID %d to pipe (%lu bytes)\n", parentProcess->shmID, sizeof(parentProcess->shmID));	
}

void parent_CloseandWrite(struct process *parentProcess){
	close(parentProcess->fd[0]);
	write(parentProcess->fd[1], &(parentProcess->shmID), sizeof(int));
	close(parentProcess->fd[1]);
}

void forked_Child(struct process *childProcess, char *str){
	close(childProcess->fd[1]);
	sprintf(str, "%d", childProcess->fd[0]);
}
