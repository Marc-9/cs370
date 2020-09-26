#ifndef CHECKER_H_INCLUDED
#define CHECKER_H_INCLUDED


struct check{
        int dividend;
        int divisor;
        int shmID;
        int pid;
	short divisible;
	char print_string[8];
};
int check_divisible(struct check *);
int convert_char_to_int(const char *);
void check_conversion_success(const char *, const char *);
void print_results(struct check *);
void print_start_info(struct check *);
#endif
