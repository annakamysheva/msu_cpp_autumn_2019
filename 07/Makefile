CXX=g++
CFLAGS= -std=c++14

all: test
	@./test

test: test.o 
	$(CXX) $(CFLAGS) test.o -o test 

test.o: test.cpp allocator.h vector.h iterator.h
	$(CXX) $(CFLAGS) -c test.cpp 


clean:
	rm *.o test