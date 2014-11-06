CXX=g++
CXXFLAGS=-std=c++1y -Wall -O3

all: build 

build: create_folder parser.o indexer.o main.o
	$(CXX) $(CXXFLAGS) build/parser.o build/indexer.o build/main.o -o build/main

create_folder:
	mkdir -p build

parser.o:
	$(CXX) $(CXXFLAGS) -c src/parser.cpp -o build/parser.o

indexer.o:
	$(CXX) $(CXXFLAGS) -c src/indexer.cpp -o build/indexer.o

main.o:
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o build/main.o

clean:
	rm -rf build
