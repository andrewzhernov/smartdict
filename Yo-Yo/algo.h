#ifndef ALGO_H_
#define ALGO_H_

#include <iostream>
#include <vector>
#include "indexer.h"

const std::string INDEX_FILE = "/home/tatiana/Yo-Yo/index";
const std::string SEPARATOR = "-----------------------";
const std::string PROGRAMNAME = "SmartDict";


class TAlgo {

public:
void ProcessIndex(const std::string argument);
void ProcessFind(const std::vector<std::string> arguments, const std::vector<std::string> arguments_minus);
void ProcessHelp();
};

#endif /* ALGO_H_ */
