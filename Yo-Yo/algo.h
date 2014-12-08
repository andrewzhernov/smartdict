#ifndef ALGO_H_
#define ALGO_H_

#include <iostream>
#include <vector>
#include "indexer.h"
#include "frequency.h"

const std::string INDEX_FILE = "index.txt";
const std::string FREQUENCY_FILE = "frequency.txt";
const std::string SEPARATOR = "-----------------------";
const std::string PROGRAMNAME = "SmartDict";


class TAlgo {
public:
	void ProcessFrequency(const std::string argument);
	void ProcessIndex(const std::string argument);
	void ProcessFind(const std::vector<std::string> arguments, const std::vector<std::string> arguments_minus);
	void ProcessHelp();
};

#endif /* ALGO_H_ */