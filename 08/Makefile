CXX=g++
CFLAGS= -std=c++14
PROGECT_NAME_H = ThreadPool.h

all: test
	@./test

test: test.o 
	$(CXX) $(CFLAGS) test.o -o test 

test.o: test.cpp $(PROGECT_NAME_H)
	$(CXX) $(CFLAGS) -c test.cpp 


clean:
	rm *.o test