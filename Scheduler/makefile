Scheduler : configuration.o Data.o ProductionLine.o Scheduler.o Test.o UI.o
	g++ -o Scheduler configuration.o Data.o ProductionLine.o Scheduler.o Test.o UI.o

debug : configuration.o Data.o ProductionLine.o Scheduler.o Test.o UI.o
	g++ -o debug configuration.o Data.o ProductionLine.o Scheduler.o Test.o UI.o -g

configuration.o : configuration.cpp configuration.h UI.h
	g++ -c configuration.cpp
Data.o : Data.cpp Data.h
	g++ -c Data.cpp
ProductionLine.o : ProductionLine.cpp ProductionLine.h 
	g++ -c ProductionLine.cpp
Scheduler.o : Scheduler.cpp Data.h ProductionLine.h Test.h UI.h configuration.h
	g++ -c Scheduler.cpp
Test.o : Test.cpp Test.h
	g++ -c Test.cpp
UI.o : UI.cpp UI.h configuration.h Data.h
	g++ -c UI.cpp
clean :	
	rm Scheduler configuration.o Data.o ProductionLine.o Scheduler.o Test.o UI.o

