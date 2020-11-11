#ifndef Task_H_INCLUDED
#define Task_H_INCLUDED
#include <ostream>
class Task{
	public:
		Task(int pid, int arrivalTime, int burstDuration, int priority = 1);
		~Task() = default;
		void alterBurstDuration(const int);
		int getPriority() const;
		int getPid() const;
		int getArrivalTime() const;
		int getBurstDuration() const;
		void taskComplete(const int);
		bool workOnTask();
		void waitOnTask();
		int getWaitingTime() const;
	private:
		int pid;
		int arrivalTime;
		int burstDuration;
		int priority;
		int waitingTime;
		//enum state { waiting, running, finished};
		//state taskState;
};
std::ostream &operator<<(std::ostream &, Task &);
#endif /*TASK_H_INCLUDED*/

