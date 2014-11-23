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
    void ProcessIndex(std::string argument);
    void ProcessFind(std::vector<std::string> argument);
    void ProcessHelp();
};

#endif /* ALGO_H_ */
