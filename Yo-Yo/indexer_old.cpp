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

void TIndexer::IndexSentence(const std::string& word, const std::string& sentence) {
    size_t block_id = Index.size();
    auto it = Index.find(word);
    if (it != Index.end()) {
        block_id = it->second;        
    } else {
        Index[word] = block_id;
        Data.push_back(std::set<std::string>());
    }
    Data[block_id].insert(sentence);
}

void TIndexer::IndexText(const std::string& text) {
    std::vector<std::string> sentences, words;
    TParser parser;
    parser.SplitText(text, sentences);
    for (const auto& sentence : sentences) {
        parser.SplitSentence(sentence, words);
        for (const auto& word : words) {
            IndexSentence(word, sentence);
        }
    }
}

void TIndexer::IndexFile(const string& filename) {
    string text;
    ifstream ifs(filename);
    getline(ifs, text, '\0');
    IndexText(text);
}

int TIndexer::FindSentencesIDs(const std::vector<std::string> words, std::vector<int>& ids) {
	for (const auto& word : words) {
		auto it = Index.find(word);
		if (it == Index.end()) return -1;
		ids.push_back(it->second);
	}
	return 0;
}

void TIndexer::FindSentences(const std::vector<std::string> words, std::vector<string>& sentences) const {
	sentences.clear();

	std::vector<int> ids;
	FindSentencesIDs(words, ids);
	for (const auto& id : ids) {
		std::vector<string> new_sentences;

		const set<string>& block = Data[id];
		new_sentences.resize(block.size());
		copy(block.begin(), block.end(), new_sentences.begin());
        if (sentences.size() == 0) sentences = new_sentences;
		else {
			std::vector<int> result(sentences.size());
			std::vector<int>::iterator end = std::set_intersection(sentences.begin(), sentences.end(), 
					new_sentences.begin(), new_sentences.end(), result.begin());
			result.resize(end - result.begin());
			sentences = result;
		}
	}
}

/*void TIndexer::FindSentences(const string& word, vector<string>& sentences) const {
    sentences.clear();

    int sentences_id = FindSentencesID(word);    
    if (sentences_id != -1) {
        const set<string>& block = Data[sentences_id];
        sentences.resize(block.size());
        copy(block.begin(), block.end(), sentences.begin());
    }
}
*/

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
