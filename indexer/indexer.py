#!/usr/bin/env python
# coding: utf8

import nltk.data
#from nltk.tokenize.punkt import PunktWordTokenizer

def run():
    tokenizer = nltk.data.load('tokenizers/punkt/english.pickle')
    text = open("data/data.txt").read().decode("utf8")
    sents = tokenizer.tokenize(text)
    out = open("data/sentences", "w")
    for sentence in sents:
        print >>out, sentence.strip().encode("utf8")

    d = {}
    i = 0
    for sentence in sents:
        words = nltk.word_tokenize(sentence)
        for word in words:
            word = word.lower()
            if word.isalpha():
                if not d.has_key(word):
                    d[word] = set()
                d[word].add(i)
        i += 1

    out = open("data/build_index", "w")
    for word in sorted(d):
        print >>out, word.encode("utf8"),
        for num in d[word]:
            print >>out, num,
        print >>out

