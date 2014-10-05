#include <iostream>
#include <vector>
#include <string>

#include "libs/indexer/indexer.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        TIndexer indexer;
        vector<string> sentences;
        indexer.LoadFromDisk("index.txt");
        indexer.Find(string(argv[1]), sentences);
        for (size_t i = 0; i < sentences.size(); ++i) {
            cout << sentences[i] << endl;
        }
    } else {
        cerr << "Usage: " << string(argv[0]) << " <word>" << endl;
    }

    return 0;
}
