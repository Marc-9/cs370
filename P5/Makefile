CXX=g++
CXXFLAGS=-Wall -Wextra -Wpedantic -Werror -Wfatal-errors -Winit-self -Wshadow -Wcomment -Wctor-dtor-privacy -Wold-style-cast -fno-diagnostics-show-option -std=c++14

all: Scheduler.cc 
	$(CXX) $(CXXFLAGS) -o Scheduler Scheduler.cc Task.cc AlgoContainer.cc Algos.cc
		
clean:
	rm -f Scheduler *.o *.zip
	
package:
	zip Ruffalo-Burgat-Jean-Marc-HW5.zip README.txt Makefile Scheduler.cc Task.cc Task.h Scheduler.h AlgoContainer.cc AlgoContainer.h Algos.cc Algos.h
