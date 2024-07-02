## Email: maayan1sher@gmail.com


CXX=g++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES= tile.cpp player.cpp board.cpp card.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

all: demo

catan: demo
		./demo

demo: Demo.o tile.cpp player.cpp  board.cpp card.cpp
	$(CXX) $(CXXFLAGS) $^ -o demo

test: test.o $(OBJECTS)
		$(CXX) $(CXXFLAGS) $^ -o test
		./test


valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test