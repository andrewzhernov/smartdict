#ifndef INDEXER_H_
#define INDEXER_H_

#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <string>

class TIndexer {
private:
    std::map<std::string, size_t> Index;
    std::vector<std::set<std::string>> Data;

public:
    bool IndexSentence(const std::string& word, const std::string& sentence);
    void LoadFromDisk(const std::string& filename);
    void SaveToDisk(const std::string& filename) const;
    void Find(const std::string& word, std::vector<std::string>& sentences) const;
};

#endif /* INDEXER_H_ */
