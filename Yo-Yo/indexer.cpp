#include "indexer.h"


void TIndexer::IndexSentence(const std::string& word, const std::string& sentence) {
    size_t block_id = WordIndex.size();
    auto it = WordIndex.find(word);
    if (it != WordIndex.end()) {
        block_id = it->second;        
    } else {
        WordIndex.insert(std::pair<std::string, int>(word, block_id));
        BlockOfSentences.push_back(std::vector<int>());
    }
    BlockOfSentences[block_id].push_back(SentenceIndex[sentence]);
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

    	for (const auto& word : words) IndexSentence(word, sentence);
    }
}

void TIndexer::IndexFile(const std::string& filename) {
    std::string text;
    std::ifstream ifs(filename);
    std::getline(ifs, text, '\0');
    IndexText(text);
}

int TIndexer::FindBlocksIDs(const std::vector<std::string> words, std::vector<int>& ids) const {
    for (const auto& word : words) {
	auto it = WordIndex.find(word);
	if (it == WordIndex.end()) return 1;
	ids.push_back(it->second);
    }
    return 0;
}

void TIndexer::FindSentences(const std::vector<std::string> words, std::vector<std::string>& sentences) const {

    std::vector<int> ids;
    if (FindBlocksIDs(words, ids)) {
	sentences.clear();
	return;
    }
    std::vector<int> block = BlockOfSentences[ids[0]];

    for (const auto& id : ids) {
	std::vector<int> next_block = BlockOfSentences[id];
	std::vector<int> result(block.size());
	std::vector<int>::iterator end = std::set_intersection(block.begin(), block.end(), 
			next_block.begin(), next_block.end(), result.begin());
	result.resize(end - result.begin());
	block.swap(result);
    }

    for (const auto& sentence_num : block) {
	sentences.push_back(Sentences[sentence_num]);
    }
}


void TIndexer::LoadFromDisk(const std::string& filename) {
    WordIndex.clear();
    BlockOfSentences.clear();
    SentenceIndex.clear();
    SentenceIndex.clear();

    size_t count, block_size;
    std::string word, sentence;
    int sentence_index = 0;

    std::ifstream ifs(filename);
    ifs >> count;
    std::getline(ifs, word);
    for (size_t i = 0; i < count; ++i) {
        std::getline(ifs, word);
        WordIndex[word] = i;
        ifs >> block_size;
        std::getline(ifs, sentence);
        BlockOfSentences.push_back(std::vector<int>());

        for (size_t j = 0; j < block_size; ++j) {
            std::getline(ifs, sentence);
			
	    if (SentenceIndex.find(sentence) != SentenceIndex.end()) {
		BlockOfSentences[i].push_back(SentenceIndex[sentence]);
	    }
	    else {
                BlockOfSentences[i].push_back(sentence_index);
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

    for (auto word_it = WordIndex.begin(); word_it != WordIndex.end(); ++word_it) {
        const std::vector<int> block = BlockOfSentences[word_it->second];
        ofs << word_it->first << '\n' << block.size() << '\n';

        for (const auto& sentence_index : block) {
            ofs << Sentences[sentence_index] << '\n';
        }

    }
}

