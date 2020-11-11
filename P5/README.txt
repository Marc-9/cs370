John Heywood once said "Rome wasn't built in a day", well then its a good thing I did not name this program Rome, because it was built in a day. But just as millions of people a day marvel at the wonderful creation that is Rome, so will they marvel at the beautifulness which is this code. Granted near the end I got a bit sloppy, with code duplication, and doing easy fixes (bools rather than enums, also I think I have a memory leak). While the code is as beautiful as Rome, it is also as fragile, so barbarians (those who feed my program bad input) can likely make my program fail.

Files
Headers [Task.h, Scheduler.h, Algos.h, AlgoContainer.h]

Scheduler.cc
	-Basically my main.cc I would have liked to have used the name Scheduler for one of my files but the documentation forces us to be able to run the program out of this file. This file opens a file that is passed in as an argument. It also initializes a Algo Container instance, which is just a vector of every task. It then parses the file line by line making tasks for each one and passing it into the Algo Container instance. Where it then closes the file, and sorts the container by Arrival time.

Task.cc
	-The class file for tasks, tasks enter with a pid, arrival time, burst duration and priority. Additionally I added a waiting time variable which gets incremented each clock cycle it waits in the queue without having done any work. The Burst duration gets decremented for each clock cycle in which work is done. The class is full of helpful methods to get relevant data from the task, alter its variables, and a nice print method.

AlgoContainer.cc
	-The main point of this class is to store every task, order them by arrival time, and run each of the algorithms on the vector. It also has methods for iterating over the vector and indexing as it is a vector of a class I created.

Algos.cc
	-Each algorithm initially had their own class, but I was able to condense them into one. The main operation of the class is the run method, which adds tasks to the queue, does work on the 0th index and adds a clock cycle to every other task in the clock cycle. The only difference between the algorithms is in deciding which task gets put in the 0th index. When a task completes it reports its wait time and turnaround time to the global variables stored in the Algos instance. Then the outputResults method will report the stats.

Running the file
./Scheduler <input_filename>

