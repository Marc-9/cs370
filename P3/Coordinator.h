#ifndef COORDINATOR_H_INCLUDED
#define COORDINATOR_H_INCLUDED


struct process{
        char *dividend;
        char *divisor;
        int shmID;
	int fd[2];
	int pid;
};
void fork_function(struct process*);
void check_arg_count(int);
void create_shared_mem_id(int *, int);
void delete_shared_mem_id(int *, int);
void forked_Parent(struct process *);
void parent_CloseandWrite(struct process *);
void forked_Child(struct process *, char *);

#endif
