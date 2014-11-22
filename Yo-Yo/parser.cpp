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
        } else {
            if (!isSentence) {
		while (text[i] == ' ' || text[i] == '\n') i++;
                isSentence = true;
                begin = i;
            }
        }
    }
}

inline bool TParser::IsLetter(char c) const {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

void TParser::SplitSentence(const std::string& sentence, std::vector<std::string>& words) const {
    words.clear();

    bool isWord = false;
    size_t begin = 0;
    for (size_t i = 0; i < sentence.size(); ++i) {
        if (IsLetter(sentence[i])) {
            if (!isWord) {
                isWord = true;
                begin = i;
            }
        } else {
           if (isWord) {
               isWord = false;
               words.push_back(sentence.substr(begin, i - begin));
           }
        }
    }
    if (begin != sentence.size() - 1) words.push_back(sentence.substr(begin, sentence.size() - begin));
}
