#include "indexer.h"

using std::ifstream;
using std::ofstream;
using std::endl;
using std::getline;
using std::copy;
using std::map;
using std::set;
using std::vector;
using std::string;

bool TIndexer::IndexSentence(const string& word, const string& sentence) {
    size_t block_id = Index.size();
    auto it = Index.find(word);
    if (it != Index.end()) {
        block_id = it->second;        
    } else {
        Index[word] = block_id;
        Data.push_back(set<string>());
    }
    Data[block_id].insert(sentence);
}

void TIndexer::LoadFromDisk(const string& filename) {
    Index.clear();
    Data.clear();

    string word, sentence;
    ifstream ifs(filename);
    size_t count, block_size;
    ifs >> count;
    for (size_t i = 0; i < count; ++i) {
        getline(ifs, word);
        Index[word] = i;
        ifs >> block_size;
        Data.push_back(set<string>());
        for (size_t j = 0; j < block_size; ++j) {
            getline(ifs, sentence);
            Data[i].insert(sentence);
        }
    }
}

void TIndexer::SaveToDisk(const string& filename) const {
    ofstream ofs(filename);
    ofs << Index.size() << endl;
    for (auto word_it = Index.begin(); word_it != Index.end(); ++word_it) {
        const set<string>& block = Data[word_it->second];
        ofs << word_it->first << endl << block.size() << endl;
        for (auto sent_it = block.begin(); sent_it != block.end(); ++sent_it) {
            ofs << *sent_it << endl;
        }
    }
}

void TIndexer::Find(const string& word, vector<string>& sentences) const {
    sentences.clear();

    auto it = Index.find(word);    
    if (it != Index.end()) {
        const set<string>& block = Data[it->second];
        copy(block.begin(), block.end(), sentences.begin());
    }
}
