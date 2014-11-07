#include <iostream>
#include "indexer.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

const string INDEX_FILE = "../data/index";
const string SEPARATOR = "-----------------------";

int main(int argc, char* argv[]) {
    if (argc == 3 && string(argv[1]) == "index") {
        TIndexer indexer;
        indexer.IndexFile(string(argv[2]));
        indexer.SaveToDisk(INDEX_FILE);
    } else if (argc == 3 && string(argv[1]) == "find") {
        vector<string> sentences;
        TIndexer indexer;
        indexer.LoadFromDisk(INDEX_FILE);
        indexer.Find(string(argv[2]), sentences);
        if (sentences.empty()) {
            cout << "Not found" << endl;
        } else {
            cout << SEPARATOR << endl;
            for (size_t i = 0; i < sentences.size(); ++i) {
                cout << sentences[i] << endl << SEPARATOR << endl;
            }
        }
    } else if (argc == 2 && string(argv[1]) == "--help") {
        cout << "AVAILABLE COMMANDS:" << endl;
        cout << string(argv[0]) << " index SOURCE_FILE" << endl;
        cout << string(argv[0]) << " find WORD" << endl;
    } else {
        cout << "Usage: " + string(argv[0]) + " --help" << endl;
    }

    return 0;
}
