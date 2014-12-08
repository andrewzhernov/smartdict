#ifndef FREQUENCY_H_
#define FREQUENCY_H_

#include <fstream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

#include "parser.h"

class FrequencyManager {
private:
	std::map<triple, int> triple_frequency_;

public:
	void CountFrequency(const std::string& filename);
	void AddNewTriple(const triple newTriple);
	void LoadFromDisk(const std::string& filename);
	void SaveToDisk(const std::string& filename) const;
	int GetSequenceFrequency(const std::string& sentence);
};

#endif /* FREQUENCY_H_ */