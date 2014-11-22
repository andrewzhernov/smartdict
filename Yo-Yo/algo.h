#ifndef ALGO_H_
#define ALGO_H_

#include <iostream>
#include <vector>
#include "indexer.h"

const std::string INDEX_FILE = "..Yo-Yo/index";
const std::string SEPARATOR = "-----------------------";
const std::string PROGRAMNAME = "SmartDict";

void process_index(std::string argument);

void process_find(std::vector<std::string> argument);

void process_help();


#endif /* ALGO_H_ */
