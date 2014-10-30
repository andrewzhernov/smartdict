#!/usr/bin/python
import string

def find(word):
    lines = open('data/build_index').readlines()
    for line in lines:
        word_indexes = line.split(' ')
        if (word_indexes[0] == word):
            return_value = []
            for index in word_indexes[1:]:
                return_value.append(int(index))
            return return_value
    return list()
