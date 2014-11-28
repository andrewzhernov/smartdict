#include "indexer.h"


void TIndexer::IndexSentence(const std::string& word, const std::string& sentence, size_t sentences_size) {
    size_t block_id = WordIndex.size();
    auto it = WordIndex.find(word);
    if (it != WordIndex.end()) {
        block_id = it->second;        
    } else {
        WordIndex.insert(std::pair<std::string, int>(word, block_id));
        BlockOfSentences.push_back(boost::dynamic_bitset<>(int(sentences_size), 0));
    }
    BlockOfSentences[block_id][SentenceIndex[sentence]] = 1;
}

void TIndexer::IndexText(const std::string& text) {
    std::vector<std::string> sentences, words;
    TParser parser;
    parser.SplitText(text, sentences);
    for (const auto& sentence : sentences) {

		int next_id = SentenceIndex.size();
		if(SentenceIndex.find(sentence) != SentenceIndex.end()) continue;

		SentenceIndex.insert(std::pair<std::string, int>(sentence, Sentences.size()));
		Sentences.push_back(sentence);
    	parser.SplitSentence(sentence, words);

    	for (const auto& word : words) IndexSentence(word, sentence, sentences.size());
    }
}

void TIndexer::IndexFile(const std::string& filename) {
    std::string text;
    std::ifstream ifs(filename);
    std::getline(ifs, text, '\0');
    IndexText(text);
}

int TIndexer::FindBlocksIDs(const std::vector<std::string> words, std::vector<int>& ids) const {
	int return_value = 0;
	for (const auto& word : words) {
		auto it = WordIndex.find(word);
		if (it == WordIndex.end()) {
			return_value = 1;
			continue;
		}
		ids.push_back(it->second);
	}
	return return_value;
}

void TIndexer::FindSentences(const std::vector<std::string> words, const std::vector<std::string> words_minus, 
							std::vector<std::string>& sentences) const {

	std::vector<int> ids;
	std::vector<int> ids_minus;
	FindBlocksIDs(words_minus, ids_minus);
	if (FindBlocksIDs(words, ids)) {
		sentences.clear();
		return;
	}
	boost::dynamic_bitset<> right_block = BlockOfSentences[ids[0]];
	for (const auto& id : ids) {
		boost::dynamic_bitset<> next_block = BlockOfSentences[id];
		right_block = right_block & next_block;
	}

	if (ids_minus.size() > 0) {	
		boost::dynamic_bitset<> false_block = BlockOfSentences[ids_minus[0]];
		for (const auto& id : ids_minus) {
			boost::dynamic_bitset<> next_block = BlockOfSentences[id];
			false_block = false_block | next_block;
		}

		right_block = right_block ^ false_block;
	}

	
	for (int i = 0; i < right_block.size(); ++i) {
		if (right_block[i]) sentences.push_back(Sentences[i]);
	}
}


void TIndexer::LoadFromDisk(const std::string& filename) {
    WordIndex.clear();
    BlockOfSentences.clear();
	SentenceIndex.clear();
	Sentences.clear();

    size_t count, block_size;
    std::string word, sentence;
	int sentence_index = 0;
	int sentences_amount;

    std::ifstream ifs(filename);
    ifs >> count;
	std::getline(ifs, word);
	ifs>> sentences_amount;
    std::getline(ifs, word);
    for (size_t i = 0; i < count; ++i) {
        std::getline(ifs, word);
        WordIndex[word] = i;
        ifs >> block_size;
        std::getline(ifs, sentence);
        BlockOfSentences.push_back(boost::dynamic_bitset<>(sentences_amount, 0));

        for (size_t j = 0; j < block_size; ++j) {
            std::getline(ifs, sentence);
			
			if (SentenceIndex.find(sentence) != SentenceIndex.end()) {
				BlockOfSentences[i][SentenceIndex[sentence]] = 1;
			}
			else {
            	BlockOfSentences[i][sentence_index] = 1;
				SentenceIndex.insert(std::pair<std::string, int>(sentence, sentence_index));
				Sentences.push_back(sentence);
				sentence_index++;
			}
        }
    }
}

void TIndexer::SaveToDisk(const std::string& filename) const {
    std::ofstream ofs(filename);
    ofs << WordIndex.size() << '\n';
	ofs << SentenceIndex.size() << '\n';

    for (auto word_it = WordIndex.begin(); word_it != WordIndex.end(); ++word_it) {
        const boost::dynamic_bitset<> block = BlockOfSentences[word_it->second];
        ofs << word_it->first << '\n' << block.count() << '\n';

        for (int i = 0; i < block.size(); ++i) {
           if (block[i] == 1) ofs << Sentences[i] << '\n';
        }

    }
}

