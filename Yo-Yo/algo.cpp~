#include "algo.h"
#include "indexer.cpp"


void TAlgo::ProcessIndex(const std::string argument) {
	TIndexer indexer;
    indexer.IndexFile(argument);
    indexer.SaveToDisk(INDEX_FILE);
}

void TAlgo::ProcessFind(const std::vector<std::string> arguments, const std::vector<std::string> arguments_minus) {
	std::vector<std::string> sentences;
    TIndexer indexer;
    indexer.LoadFromDisk(INDEX_FILE);
    indexer.FindSentences(arguments, arguments_minus, sentences);
    if (sentences.empty()) {
        std::cout << "Not found" << '\n';
    } 
	else {
        std::cout << SEPARATOR << '\n';
        for (size_t i = 0; i < sentences.size(); ++i) {
            std::cout << sentences[i] << '\n' << SEPARATOR << '\n';
        }
    }
}

void TAlgo::ProcessHelp() {
	std::cout << "AVAILABLE COMMANDS:" << '\n';
    std::cout << PROGRAMNAME << " index SOURCE_FILE" << '\n';
    std::cout << PROGRAMNAME << " find WORDS" << '\n';
}















