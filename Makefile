CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic

.PHONY: all clean

# Build all three versions.
all: students-vector students-list students-deque

students-vector: $(wildcard *.cpp *.h)
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@

students-list: $(wildcard list/*.cpp list/*.h)
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@

students-deque: $(wildcard deque/*.cpp deque/*.h)
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@

# Remove only the compiled programs.
clean:
	rm -f students-vector students-list students-deque