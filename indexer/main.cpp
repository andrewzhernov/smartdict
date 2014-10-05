#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

#include "libs/parser/parser.h"
#include "libs/indexer/indexer.h"

using std::ifstream;
using std::getline;
using std::string;
using std::vector;

int main() {
    TParser parser;
    TIndexer indexer;

    string text;
    ifstream ifs("../data/data.txt");
    getline(ifs, text, '\0');

    vector<string> sentences;
    parser.SplitText(text, sentences);
    for (size_t i = 0; i < sentences.size(); ++i) {
        vector<string> words;
        parser.SplitSentence(sentences[i], words);
        for (size_t j = 0; j < words.size(); ++j) {
            indexer.IndexSentence(words[j], sentences[i]);
        }
    }

    indexer.SaveToDisk("index.txt");

    return 0;
}
