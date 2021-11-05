# %%
import re
word_pattern = r'^[a-z]+$'

words = open('words.txt', 'r')
dictionary = open('dictionary.txt', 'w')
for word in words.readlines():
    if re.match(word_pattern, word):
        dictionary.write(word)

# %%
