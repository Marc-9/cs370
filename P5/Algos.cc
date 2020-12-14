#include <string>
#include <iostream>
#include <iomanip>
#include "Algos.h"


using namespace std;

Algos::Algos(int algoType){
	this->turnAroundTime = 0;
	this->waitingTime = 0;
	this->clockCount = 0;
	if(algoType == 1){
		this->isPriority = true;
		this->isSJF = false;
	}
	else if(algoType == 2){
		this->isPriority = false;
		this->isSJF = true;
	}
	else{
		this->isPriority = false;
		this->isSJF = false;
	}

}

void Algos::addToQueue(const Task newTask){
	this->queue.push_back(newTask);
}

void Algos::removeFromQueue(){
	this->queue.erase(this->queue.begin());
}

void Algos::incrementClock(){
	this->clockCount++;
}

int Algos::getClockCount(){
	return this->clockCount;
}

void Algos::increaseTimeVariables(const int runningTime, const int timeWaiting){
	this->turnAroundTime += runningTime;
	this->waitingTime += timeWaiting;
}

void Algos::averageTime(const int totalTasks){
	this->turnAroundTime /= totalTasks;
	this->waitingTime /= totalTasks;
}

void Algos::resetValues(){
	this->turnAroundTime = 0;
	this->waitingTime = 0;
	this->clockCount = 0;
	this->queue.clear();
}

double Algos::getTurnAroundTime(){
	return this->turnAroundTime;
}

double Algos::getWaitingTime(){
	return this->waitingTime;
}

void Algos::run(const int lastArrivalTime, const vector<Task> &taskPool){
	unsigned indexOfNextTask = 0;
	while(this->getClockCount() <= lastArrivalTime || this->size() > 0){
		this->addTasksToQueue(indexOfNextTask, taskPool);
		this->incrementClock();
		this->operationsOnQueue();	
	}
	this->averageTime(taskPool.size());
	outputResults(taskPool.size());
}

void Algos::operationsOnQueue(){
	if(this->size() >= 1){
		this->sortByAlgo();
		for(unsigned i = 1; i < this->size(); i++){
        	this->get(i).waitOnTask();
        }
        if(this->get(0).workOnTask()){
        	int tempRunningTime = this->getClockCount() - this->get(0).getArrivalTime();
        	this->increaseTimeVariables(tempRunningTime, this->get(0).getWaitingTime());
        	this->removeFromQueue();
        }       
    }

}

void Algos::addTasksToQueue(unsigned &indexOfNextTask, const vector<Task> &taskPool){
	while(this->getClockCount() >= taskPool[indexOfNextTask].getArrivalTime() && indexOfNextTask < taskPool.size()){
        this->addToQueue(taskPool[indexOfNextTask]);
        ++indexOfNextTask;
    }
    
}

void Algos::outputResults(int taskPoolSize){
	cout << "--- " << this->returnAlgoName() << " ---" << "\n";
	cout << fixed;
  	cout << setprecision(3);
	cout << "Average Turnaround Time: " << this->getTurnAroundTime() << "\n";
	cout << "Average Waiting Time: "  << this->getWaitingTime() << "\n";
	cout << "Throughput: " << taskPoolSize / double(this->getClockCount()) <<  "\n";
}

string Algos::returnAlgoName(){
	if(this->isPriority){
		return "Priority";
	}
	else if(this->isSJF){
		return "SJFP";
	}
	else{
		return "FCFS";
	}
}


void Algos::sortByAlgo(){
	if(this->isPriority){
		this->sortByPriority();
	}
	else if(this->isSJF){
		this->sortByShortest();
	}
}

void Algos::sortByShortest(){
	if(this->size() < 2){
		return;
	}
	int minDuration = this->get(0).getBurstDuration();
	int maxPriority = this->get(0).getPriority();
	int maxIndex = 0;
	for(unsigned i = 1; i < this->size(); i++){
		if(this->get(i).getBurstDuration() == minDuration){
			if(this->get(i).getPriority() < maxPriority){
				minDuration = this->get(i).getBurstDuration();
				maxPriority = this->get(i).getPriority();
				maxIndex = i;
			}
		}
		else if(this->get(i).getBurstDuration() < minDuration){
			minDuration = this->get(i).getBurstDuration();
			maxPriority = this->get(i).getPriority();
			maxIndex = i;
		}
	}
	if(maxIndex != 0){
		Task tempTask = this->get(0);
		this->queue[0] = this->queue[maxIndex];
		this->queue[maxIndex] = tempTask;
	}
}

void Algos::sortByPriority(){
	if(this->size() < 2){
		return;
	}
	int maxpriority = this->get(0).getPriority();
	int minDuration = this->get(0).getBurstDuration();
	int maxIndex = 0;
	for(unsigned i = 1; i < this->size(); i++){
		if(this->get(i).getPriority() == maxpriority){
			if(this->get(i).getBurstDuration() < minDuration){
				maxpriority = this->get(i).getPriority();
				minDuration = this->get(i).getBurstDuration();
				maxIndex = i;
			}
		}
		else if(this->get(i).getPriority() < maxpriority){
			maxpriority = this->get(i).getPriority();
			minDuration = this->get(i).getBurstDuration();
			maxIndex = i;
		}
	}
	if(maxIndex != 0){
		Task tempTask = this->get(0);
		this->queue[0] = this->queue[maxIndex];
		this->queue[maxIndex] = tempTask;
	}
}


Algos::iterator Algos::begin() const{
	return this->queue.begin();
}

Algos::iterator Algos::end() const{
	return this->queue.end();
}

size_t Algos::size() const{
	return queue.size();
}

Task & Algos::get(const size_t i){
	return queue[i];
}

Task &Algos::operator[](const size_t i){
	return queue[i];
}
