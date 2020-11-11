#ifndef Scheduler_H_INCLUDED
#define Scheduler_H_INCLUDED
#include "AlgoContainer.h"


void argumentChecking(int);
void parseTask(std::string &, AlgoContainer &);
void split(std::string &,std::vector<int> &);

#endif