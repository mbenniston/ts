all : ts

ts : ts.cpp TaskList.o
	$(CXX) ts.cpp TaskList.o -o ts -O3

TaskList.o : TaskList.cpp TaskList.hpp
	$(CXX) -c TaskList.cpp -o TaskList.o -O3

run : ts
	./ts

clean : 
	rm -f ts TaskList.o
