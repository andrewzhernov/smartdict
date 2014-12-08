#include "frequency.h"

void FrequencyManager::AddNewTriple(const triple newTriple) {
	auto it = triple_frequency_.find(newTriple);
	if (it != triple_frequency_.end()){
		++triple_frequency_[newTriple];
	}
	else {
		triple_frequency_.insert(std::pair<triple, int>(newTriple, 1));
	}
}

void FrequencyManager::CountFrequency(const std::string& filename) {
	std::string text;
	std::ifstream ifs(filename);
	std::getline(ifs, text, '\0');
	
	TParser parser;
	std::vector<std::string> sentences;
	parser.SplitText(text, sentences);

	std::map<triple, int> tripleFrequency;
	for (auto sentence : sentences) {
		std::vector<triple> sentenceTriples;
		parser.SplitSentenceIntoTriples(sentence, sentenceTriples);
		for (auto newTriple : sentenceTriples) {
			AddNewTriple(newTriple);
		}
	}
}

int FrequencyManager::GetSequenceFrequency(const std::string& sentence) {
	TParser parser;
	std::vector<triple> sentenceTriples;
	parser.SplitSentenceIntoTriples(sentence, sentenceTriples);
	
	int sentenceFrequency = 0;
	for (triple t : sentenceTriples) {
		sentenceFrequency += triple_frequency_[t];
	}
	return sentenceFrequency;
}

void FrequencyManager::SaveToDisk(const std::string& filename) const {
	std::ofstream ofs(filename);
	ofs << triple_frequency_.size() << '\n';

	for (auto it = triple_frequency_.begin(); it != triple_frequency_.end(); ++it) {
		ofs << get<0>(it->first) << " " << get<1>(it->first) << " " << get<2>(it->first) << " " << it->second << '\n';
	}
}

void FrequencyManager::LoadFromDisk(const std::string& filename) {
	triple_frequency_.clear();
	int numberOfTriples;
	std::ifstream ifs(filename);
	ifs >> numberOfTriples;
	for (size_t i = 0; i < numberOfTriples; ++i) {
		int frequency;
		string first;
		string second;
		string third;
		ifs >> first >> second >> third >> frequency;
		triple newTriple(first, second, third);
		triple_frequency_.insert(std::pair<triple, int>(newTriple, frequency));
	}
}
