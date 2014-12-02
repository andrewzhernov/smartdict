#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

class TParser {
private:
	inline bool IsSentenceSeparator(char c) const;

public:
	void SplitText(const std::string& text, std::vector<std::string>& sentences) const;
	void SplitSentence(const std::string& sentence, std::vector<std::string>& words) const;
};

#endif /* PARSER_H_ */
