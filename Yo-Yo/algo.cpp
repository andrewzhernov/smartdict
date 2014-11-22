#include "algo.h"



void process_index(std::string argument) {
	TIndexer indexer;
    indexer.IndexFile(argument);
    indexer.SaveToDisk(INDEX_FILE);
}

void process_find(std::vector<std::string> arguments) {
	std::vector<std::string> sentences;
    TIndexer indexer;
    indexer.LoadFromDisk(INDEX_FILE);
    indexer.FindSentences(arguments, sentences);
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

void process_help() {
	std::cout << "AVAILABLE COMMANDS:" << '\n';
    std::cout << PROGRAMNAME << " index SOURCE_FILE" << '\n';
    std::cout << PROGRAMNAME << " find WORD" << '\n';
}















