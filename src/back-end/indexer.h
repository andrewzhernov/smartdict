#ifndef INDEXER_H_
#define INDEXER_H_

#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <string>

#include "parser.h"

class TIndexer {
private:
    std::map<std::string, size_t> Index;
    std::vector<std::set<std::string>> Data;

    void IndexSentence(const std::string& word, const std::string& sentence);

public:
    void IndexText(const std::string& text);
    void IndexFile(const std::string& filename);
    void Find(const std::string& word, std::vector<std::string>& sentences) const;

    void LoadFromDisk(const std::string& filename);
    void SaveToDisk(const std::string& filename) const;
};

#endif /* INDEXER_H_ */
