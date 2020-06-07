CXX=g++
CFLAGS= -std=c++14

all: test
	@./test

test: test.o bigint.o
	$(CXX) $(CFLAGS) test.o bigint.o -o test 

test.o: test.cpp bigint.h
	$(CXX) $(CFLAGS) -c test.cpp 

parser.o: bigint.cpp bigint.h
	$(CXX) $(CFLAGS) -c bigint.cpp 

clean:
	rm *.o test