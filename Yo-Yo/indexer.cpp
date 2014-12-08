#include "indexer.h"
#include "frequency.h"

using namespace std;

void TIndexer::IndexSentence(const std::string& word, const std::string& sentence, size_t sentences_size) {
	size_t block_id = word_index_.size();
	auto it = word_index_.find(word);
	if (it != word_index_.end()) {
		block_id = it->second;
	}
	else {
		word_index_.insert(std::pair<std::string, int>(word, block_id));
		block_of_sentences_.push_back(boost::dynamic_bitset<>(int(sentences_size), 0));
	}
	block_of_sentences_[block_id][sentence_index_[sentence]] = 1;
}

void TIndexer::IndexText(const std::string& text) {
	std::vector<std::string> sentences, words;
	TParser parser;
	parser.SplitText(text, sentences);
	for (const auto& sentence : sentences) {
		if (sentence_index_.find(sentence) == sentence_index_.end()) {
			sentence_index_.insert(std::pair<std::string, int>(sentence, sentences_.size()));
			sentences_.push_back(sentence);
			parser.SplitSentence(sentence, words);

			for (const auto& word : words) {
				IndexSentence(word, sentence, sentences.size());
			}
		}
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
		auto it = word_index_.find(word);
		if (it == word_index_.end()) {
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
	boost::dynamic_bitset<> right_block = block_of_sentences_[ids[0]];
	for (const auto& id : ids) {
		boost::dynamic_bitset<> next_block = block_of_sentences_[id];
		right_block = right_block & next_block;
	}

	if (ids_minus.size() > 0) {
		boost::dynamic_bitset<> false_block = block_of_sentences_[ids_minus[0]];
		for (const auto& id : ids_minus) {
			boost::dynamic_bitset<> next_block = block_of_sentences_[id];
			false_block = false_block | next_block;
		}
		right_block = right_block ^ false_block;
	}

	for (size_t i = 0; i < right_block.size(); ++i) {
		if (right_block[i]) sentences.push_back(sentences_[i]);
	}
}

void TIndexer::LoadFromDisk(const std::string& filename) {
	word_index_.clear();
	block_of_sentences_.clear();
	sentence_index_.clear();
	sentences_.clear();

	size_t count, block_size;
	std::string word, sentence;
	int sentence_index = 0;
	int sentences_amount;

	std::ifstream ifs(filename);
	ifs >> count;
	std::getline(ifs, word);
	ifs >> sentences_amount;
	std::getline(ifs, word);
	for (size_t i = 0; i < count; ++i) {
		std::getline(ifs, word);
		word_index_[word] = i;
		ifs >> block_size;
		std::getline(ifs, sentence);
		block_of_sentences_.push_back(boost::dynamic_bitset<>(sentences_amount, 0));

		for (size_t j = 0; j < block_size; ++j) {
			std::getline(ifs, sentence);

			if (sentence_index_.find(sentence) != sentence_index_.end()) {
				block_of_sentences_[i][sentence_index_[sentence]] = 1;
			}
			else {
				block_of_sentences_[i][sentence_index] = 1;
				sentence_index_.insert(std::pair<std::string, int>(sentence, sentence_index));
				sentences_.push_back(sentence);
				sentence_index++;
			}
		}
	}
}

void TIndexer::SaveToDisk(const std::string& filename) const {
	std::ofstream ofs(filename);
	ofs << word_index_.size() << '\n';
	ofs << sentence_index_.size() << '\n';

	FrequencyManager fManager;
	fManager.LoadFromDisk("frequency.txt");
	
	for (auto word_it = word_index_.begin(); word_it != word_index_.end(); ++word_it) {
		const boost::dynamic_bitset<> block = block_of_sentences_[word_it->second];

		priority_queue<pair<int, string> > ranked_sentences;

		for (size_t i = 0; i < block.size(); ++i) {
			if (block[i] == 1) {
				int rating = fManager.GetSequenceFrequency(sentences_[i]);
				ranked_sentences.push(make_pair(rating, sentences_[i]));
			}
		}

		int block_size = min((int)block.count(), 20);
		ofs << word_it->first << '\n' << block_size << '\n';
		for (int i = 0; i < block_size; ++i) {
			ofs << ranked_sentences.top().second << '\n';
			ranked_sentences.pop();
		}
	}
}
