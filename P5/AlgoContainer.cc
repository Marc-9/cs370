#include "AlgoContainer.h"
#include "Algos.h"
#include <iostream>

using namespace std;

void AlgoContainer::addTask(const Task newTask){
	this->allTasks.push_back(newTask);
}


void AlgoContainer::runFCFS(){
	this->checkArgSize();
	Algos FCFS = Algos();
	FCFS.run(allTasks[allTasks.size()-1].getArrivalTime(), this->allTasks);
	
	
}

void AlgoContainer::runPriority(){
	this->checkArgSize();
	Algos PriorityScheduling(1);
	PriorityScheduling.run(allTasks[allTasks.size()-1].getArrivalTime(), this->allTasks);

	
}

void AlgoContainer::runSJF(){
	this->checkArgSize();
	Algos SJFP(2);
	SJFP.run(allTasks[allTasks.size()-1].getArrivalTime(), this->allTasks);

}

void AlgoContainer::checkArgSize(){
	if(this->size() == 0){
		cerr << "ERROR: Please pass in tasks before running one of the scheduling algorithms\n";
		exit(1);
	}
}


//The below methods are for operating on and sorting all the tasks in the vector All tasks

AlgoContainer::iterator AlgoContainer::begin() const{
	return this->allTasks.begin();
}

AlgoContainer::iterator AlgoContainer::end() const{
	return this->allTasks.end();
}

size_t AlgoContainer::size() const{
	return allTasks.size();
}

Task &AlgoContainer::operator[](const size_t i){
        return allTasks[i];
}

ostream &operator<<(ostream &stream, AlgoContainer &container) {
	for(size_t i = 0; i < container.size(); i++){
                stream << container[i] << "\n";
    }
	return stream;
}

struct priority_sort{
	inline bool operator() (const Task& task1, const Task& task2){
		if(task1.getArrivalTime() == task2.getArrivalTime()){
			return task1.getPid() < task2.getPid();
		}
		else{
			return task1.getArrivalTime() < task2.getArrivalTime();
		}
	}
};

void AlgoContainer::sortByArrival(){
	sort(allTasks.begin(), allTasks.end(), priority_sort());
}
