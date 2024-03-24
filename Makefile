DRIVER_NAME = main
SUBMIT_NAME = submit
CXXFLAGS = -std=c++11


p4: main.o graphComp.o MinHeap.o graphBuildOps.o
	g++ $(CXXFLAGS) -o p4 main.o graphComp.o MinHeap.o graphBuildOps.o

main.o: main.cpp MinHeap.cpp graphBuildOps.h
	g++ $(CXXFLAGS) -c main.cpp

graphComp.o: graphComp.cpp
	g++ $(CXXFLAGS) -c graphComp.cpp

MinHeap.o: MinHeap.cpp
	g++ $(CXXFLAGS) -c MinHeap.cpp

graphBuildOps.o: graphBuildOps.cpp graphBuildOps.h
	g++ $(CXXFLAGS) -c graphBuildOps.cpp

clean: 
	rm -f p4 a.out *.o
