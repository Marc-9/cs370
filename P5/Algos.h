#ifndef algos_H_INCLUDED
#define algos_H_INCLUDED
#include <vector>
#include <string>
#include "Task.h"


class Algos{
	private:
		std::vector<Task> queue;
		double turnAroundTime;
		double waitingTime;
		int clockCount;
		void operationsOnQueue();
		void addTasksToQueue(unsigned &, const std::vector<Task> &);
		double getTurnAroundTime();
		void increaseTimeVariables(const int, const int);
		void averageTime(const int);
		bool isPriority;
		bool isSJF;
		void sortByAlgo();
		std::string returnAlgoName();

	public:
		Algos(int algoType = 0);
		~Algos() = default;
		void addToQueue(const Task);
		void removeFromQueue();
		using iterator = decltype(queue)::const_iterator;
		iterator begin() const;
		iterator end() const;
		size_t size() const;
		Task &operator[](const size_t);
		void run(const int, const std::vector<Task> &);
		void incrementClock();
		int getClockCount();
		Task &get(const size_t);
		double getWaitingTime();
		void sortByShortest();
		void sortByPriority();
		void outputResults(int);
		void resetValues();

};

#endif