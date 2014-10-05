#include "parser.h"

using std::string;
using std::vector;

void TParser::SplitText(const string& text, vector<string>& sentences) const {
    sentences.clear();

    bool isSentence = false;
    size_t begin = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] != '.') {
            if (!isSentence) {
                isSentence = true;
                begin = i;
            }
        } else {
            if (isSentence) {
                isSentence = false;
                sentences.push_back(text.substr(begin, i - begin));
            }
        }
    }
}

inline bool TParser::IsLetter(char c) const {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

void TParser::SplitSentence(const string& sentence, vector<string>& words) const {
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
}
