CXX=g++
CFLAGS=-c -std=c++14
ALLOCATOR=allocator.cpp

GLOBAL_TEST_BINARY=tests
GLOBAL_TEST_OBJECTS=allocator.o test_one.o

TEST_ONE=test_one.cpp
TEST_ONE_OBJECTS=allocator.o test_one.o
TEST_ONE_BINARY=test_one

all:
	allocator.o test_one.o
	$(CXX) $(GLOBAL_TEST_OBJECTS) -o $(GLOBAL_TEST_BINARY)

test_one:
	$(CXX) $(TEST_ONE_OBJECTS) -o $(TEST_ONE_BINARY)
	@./$(TEST_ONE_BINARY)

test_one.o:
	$(CXX) $(CFLAGS) $(TEST_ONE)

allocator.o:
	$(CXX) $(CFLAGS) $(ALLOCATOR)

clean:
	rm -rf *.o
	rm -rf $(GLOBAL_TEST_BINARY) $(TEST_ONE_BINARY)