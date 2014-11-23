#include <iostream>
#include "algo.h"


int main(int argc, char* argv[]) {

    TAlgo algo;

    if (argc == 3 && std::string(argv[1]) == "index") {
        algo.ProcessIndex(std::string(argv[2]));
    } 
    else if (argc >= 3 && std::string(argv[1]) == "find") {
	std::vector<std::string> arguments;
	for (int i = 2; i < argc; ++i) {
	    arguments.push_back(std::string(argv[i]));
	}
        algo.ProcessFind(arguments);  
    } 
    else if (argc == 2 && std::string(argv[1]) == "--help") {
        algo.ProcessHelp();
    } 
    else {
        std::cout << "Usage: " + std::string(argv[0]) + " --help" << '\n';
    }

    return 0;
}
