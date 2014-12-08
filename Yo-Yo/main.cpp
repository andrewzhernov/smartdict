#include <iostream>
#include "algo.h"

int main(int argc, char* argv[]) {
	TAlgo algo;

	if (argc == 3 && std::string(argv[1]) == "count_frequency") {
		algo.ProcessFrequency(std::string(argv[2]));
	}
	else if (argc == 3 && std::string(argv[1]) == "index") {
		algo.ProcessIndex(std::string(argv[2]));
	}
	else if (argc >= 3 && std::string(argv[1]) == "find") {
		std::vector<std::string> arguments;
		std::vector<std::string> arguments_minus;
		arguments_minus.clear();
		arguments.clear();
		for (int i = 2; i < argc; ++i) {
			std::string word = std::string(argv[i]);
			if (word[0] == '-') arguments_minus.push_back(std::string(word.begin() + 1, word.end()));
			else arguments.push_back(word);
		}
		algo.ProcessFind(arguments, arguments_minus);
	}
	else if (argc == 2 && std::string(argv[1]) == "--help") {
		algo.ProcessHelp();
	}
	else {
		std::cout << "Usage: " + std::string(argv[0]) + " --help" << '\n';
	}
	return 0;
}