#include "parser.h"

inline bool TParser::IsSentenceSeparator(char c) const {
	return c == '.' || c == '!' || c == '?';
}

void TParser::SplitText(const std::string& text, std::vector<std::string>& sentences) const {
	sentences.clear();
	bool isSentence = false;
	size_t begin = 0;
	for (size_t i = 0; i < text.size(); ++i) {
		if (IsSentenceSeparator(text[i])) {
			if (isSentence) {
				isSentence = false;
				sentences.push_back(text.substr(begin, i - begin));
			}
		}
		else {
			if (!isSentence) {
				while (text[i] == ' ' || text[i] == '\n') i++;
				isSentence = true;
				begin = i;
			}
		}
	}
}

void TParser::SplitSentenceIntoTriples(const std::string& sentence, std::vector<triple>& triples) const {
	std::vector<std::string> words;
	SplitSentence(sentence, words);
	triples.clear();
	for (size_t i = 0; i < words.size() - 2; ++i) {
		triple newtriple = make_tuple(words[i], words[i + 1], words[i + 2]);
		triples.push_back(newtriple);
	}
}

void TParser::SplitSentence(const std::string& sentence, std::vector<std::string>& words) const {
	words.clear();
	bool isWord = false;
	size_t begin = 0;
	for (size_t i = 0; i < sentence.size(); ++i) {
		if (isalpha(sentence[i])) {
			if (!isWord) {
				isWord = true;
				begin = i;
			}
		}
		else {
			if (isWord) {
				isWord = false;
				std::string newWord = sentence.substr(begin, i - begin);
				for (size_t j = 0; j < newWord.size(); ++j) {
					newWord[j] = tolower(newWord[j]);
				}
				words.push_back(newWord);
			}
		}
	}
	if (begin != sentence.size() - 1) {
		std::string newWord = sentence.substr(begin, sentence.size() - begin);
		for (size_t j = 0; j < newWord.size(); ++j) {
			newWord[j] = tolower(newWord[j]);
		}
		words.push_back(newWord);
	}
}