#ifndef AlgoContainer_H_INCLUDED
#define AlgoContainer_H_INCLUDED

#include <vector>
#include "Task.h"
#include <iterator>



class AlgoContainer{
	private:
		std::vector<Task> allTasks;
		void checkArgSize();

	public:
		AlgoContainer() = default;
		void addTask(const Task);
		~AlgoContainer() = default;
		using iterator = decltype(allTasks)::const_iterator;
		iterator begin() const;
		iterator end() const;
		size_t size() const;
		Task &operator[](const size_t i);
		void sortByArrival();
		void runFCFS();
		void runPriority();
		void runSJF();

};

std::ostream &operator<<(std::ostream &, AlgoContainer &);
#endif /*AlgoContainer_H_INCLUDED*/