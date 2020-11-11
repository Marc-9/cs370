#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Task.h"
#include "Scheduler.h"
#include "AlgoContainer.h"

using namespace std;
int main(int argc, char *argv[]){
	argumentChecking(argc);
	fstream inputFile;
	inputFile.open(argv[1]);

	AlgoContainer taskStructure;
	if(!inputFile.is_open()){
		cerr << "Error: " << argv[1] << " is not a valid filename\n";
		exit(1);
	}
	else{
		string taskLine;
		while(getline(inputFile, taskLine)){
			parseTask(taskLine, taskStructure);
		}
	}
	inputFile.close();

	taskStructure.sortByArrival();

	taskStructure.runFCFS();
	taskStructure.runSJF();
	taskStructure.runPriority();

	return 0;
}

void argumentChecking(int argc){
	if(argc != 2){
		cerr << "Error: Please only pass two arguments: ./Scheduler <input_filename> \n";
		exit(1);
	}
}

void parseTask(string &taskLine, AlgoContainer &taskStructure){
	vector<int> taskClassMembers;
	split(taskLine, taskClassMembers);
	if(taskClassMembers.size() != 4){
		cerr << "Invalid input detected\n";
		exit(1);
	}
	Task newTask(taskClassMembers[0],taskClassMembers[1],taskClassMembers[2],taskClassMembers[3]);
	taskStructure.addTask(newTask);

}

void split(string &taskLine,vector<int> &taskClassMembers){
	string tempstring;
	try{       
		stringstream stringstream(taskLine);
        while(getline(stringstream,tempstring,',')){
        	int stringConversion = stoi(tempstring,nullptr,10);
	        taskClassMembers.push_back(stringConversion);
        }

	}
 	catch(runtime_error &e){
        cerr << "Invalid input detected- " << tempstring << "\n";
        exit(1);
    }
}
