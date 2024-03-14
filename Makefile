DRIVER_NAME = main
SUBMIT_NAME = submit


p4: $(DRIVER_NAME).o graph.o
	g++ -o p4 $(DRIVER_NAME).o graph.o

$(DRIVER_NAME).o: $(DRIVER_NAME).cpp $(DRIVER_NAME).h graph.h
	g++ -c $(DRIVER_NAME).cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp


.PHONY: submit clean

submit:
	rm -f $(SUBMIT_NAME).zip
	zip $(SUBMIT_NAME).zip Makefile $(DRIVER_NAME).cpp $(DRIVER_NAME).h graph.cpp graph.h


clean: 
	rm -f p4 a.out *.o