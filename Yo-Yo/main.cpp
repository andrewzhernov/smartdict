#include <iostream>
#include "algo.h"


int main(int argc, char* argv[]) {

    if (argc == 3 && std::string(argv[1]) == "index") {
        process_index(std::string(argv[2]));
    } 
	else if (argc >= 3 && std::string(argv[1]) == "find") {
		std::vector<std::string> arguments;
		for (int i = 2; i < argc; ++i) {
			arguments.push_back(std::string(argv[i]));
		}
        process_find(arguments);  
    } 
	else if (argc == 2 && std::string(argv[1]) == "--help") {
        process_help();
    } 
	else {
        std::cout << "Usage: " + std::string(argv[0]) + " --help" << '\n';
    }

    return 0;
}
