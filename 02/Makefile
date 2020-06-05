CXX=g++
CFLAGS= -std=c++11

all: test
	@./test

test: test.o parser.o
	$(CXX) $(CFLAGS) test.o parser.o -o test 

test.o: test.cpp parser.h
	$(CXX) $(CFLAGS) -c test.cpp 

parser.o: parser.cpp parser.h
	$(CXX) $(CFLAGS) -c parser.cpp 

clean:
	rm *.o test