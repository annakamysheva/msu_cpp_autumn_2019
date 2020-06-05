CXX=g++
CFLAGS= -std=c++14

all: test
	@./test

test: test.o matrix.o
	$(CXX) $(CFLAGS) test.o matrix.o -o test 

test.o: test.cpp matrix.h
	$(CXX) $(CFLAGS) -c test.cpp 

matrix.o: matrix.cpp matrix.h
	$(CXX) $(CFLAGS) -c matrix.cpp 

clean:
	rm *.o test