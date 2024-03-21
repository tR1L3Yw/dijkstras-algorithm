DRIVER_NAME = main
SUBMIT_NAME = submit
CXXFLAGS = -std=c++11 -Wall -Wextra


p4: main.o graphComp.o MinHeap.o graphBuildOps.o
	g++ $(CXXFLAGS) -o p4 main.o graphComp.o MinHeap.o graphBuildOps.o

main.o: main.cpp main.h graphComp.h MinHeap.h graphBuildOps.h
	g++ $(CXXFLAGS) -c main.cpp

graphComp.o: graphComp.cpp graphComp.h
	g++ $(CXXFLAGS) -c graphComp.cpp

MinHeap.o: MinHeap.cpp MinHeap.h
	g++ $(CXXFLAGS) -c MinHeap.cpp

graphBuildOps.o: graphBuildOps.cpp graphBuildOps.h
	g++ $(CXXFLAGS) -c graphBuildOps.cpp

clean: 
	rm -f p4 a.out *.o