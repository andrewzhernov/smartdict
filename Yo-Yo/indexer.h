#ifndef INDEXER_H_
#define INDEXER_H_

#include <fstream>
#include <algorithm>
#include <map>
#include <bitset>
#include <vector>
#include <string>
#include <boost/dynamic_bitset.hpp>

#include "parser.h"

class TIndexer {
private:
    std::map<std::string, size_t> WordIndex;
    std::vector<boost::dynamic_bitset<> > BlockOfSentences;
	std::map<std::string, int> SentenceIndex;
	std::vector<std::string> Sentences;

	int FindBlocksIDs(const std::vector<std::string> words, std::vector<int>& ids) const;
    void IndexSentence(const std::string& word, const std::string& sentence, size_t sentences_size);

public:
    void IndexText(const std::string& text);
    void IndexFile(const std::string& filename);
    void FindSentences(const std::vector<std::string> words, const std::vector<std::string> words_minus, std::vector<std::string>& sentences) const;

    void LoadFromDisk(const std::string& filename);
    void SaveToDisk(const std::string& filename) const;
};

#endif /* INDEXER_H_ */
