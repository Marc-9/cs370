#include <iostream>
#include "Task.h"
using namespace std;

Task::Task(int processid, int arrival, int burst, int importance):
	pid{processid}, arrivalTime{arrival}, burstDuration{burst}, priority{importance}, waitingTime{0}
	{}

void Task::alterBurstDuration(const int timeRan){
	this->burstDuration -= timeRan;
}

int Task::getPriority() const{
	return this->priority;
}

int Task::getPid() const{
	return this->pid;
}

int Task::getArrivalTime() const{
	return this->arrivalTime;
}

int Task::getBurstDuration() const{
	return this->burstDuration;
}

void Task::waitOnTask(){
	this->waitingTime++;
}

int Task::getWaitingTime() const{
	return this->waitingTime;
}

bool Task::workOnTask(){
	this->burstDuration -= 1;
	if(this->burstDuration == 0){
		return true;
	}
	else{
		return false;
	}
}


ostream &operator<<(ostream &stream, Task &taskData) {
	return stream << "PID- " << taskData.getPid() << ", Priority- " << taskData.getPriority()
	<< ", Arrival Time- " << taskData.getArrivalTime() << ", Burst Duration- " << taskData.getBurstDuration() << ", Waiting Time- " << taskData.getWaitingTime();
}

