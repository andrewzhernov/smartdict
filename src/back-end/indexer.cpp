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

void TIndexer::IndexSentence(const string& word, const string& sentence) {
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

void TIndexer::IndexText(const string& text) {
    vector<string> sentences, words;
    TParser parser;
    parser.SplitText(text, sentences);
    for (size_t i = 0; i < sentences.size(); ++i) {
        parser.SplitSentence(sentences[i], words);
        for (size_t j = 0; j < words.size(); ++j) {
            IndexSentence(words[j], sentences[i]);
        }
    }
}

void TIndexer::IndexFile(const string& filename) {
    string text;
    ifstream ifs(filename);
    getline(ifs, text, '\0');
    IndexText(text);
}

void TIndexer::Find(const string& word, vector<string>& sentences) const {
    sentences.clear();

    auto it = Index.find(word);    
    if (it != Index.end()) {
        const set<string>& block = Data[it->second];
        sentences.resize(block.size());
        copy(block.begin(), block.end(), sentences.begin());
    }
}

void TIndexer::LoadFromDisk(const string& filename) {
    Index.clear();
    Data.clear();

    size_t count, block_size;
    string word, sentence;
    ifstream ifs(filename);
    ifs >> count;
    getline(ifs, word);
    for (size_t i = 0; i < count; ++i) {
        getline(ifs, word);
        Index[word] = i;
        ifs >> block_size;
        getline(ifs, sentence);
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
