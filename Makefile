CXX=g++
CXXFLAGS=-std=c++1y -Wall -O3

all:
	mkdir -p build
	$(CXX) $(CXXFLAGS) src/back-end/*.cpp -o build/main

clean:
	rm -rf build
