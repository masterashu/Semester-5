import os
from stop_words import stop_words, ignore_char
from split_dict import SplitDict
from collections import Counter


# Reading the files from the dataset
# and removing the stop words and special characters
# and adding it to the dictionary
def createDictionary():
    invIdx = SplitDict()

    data_dir = os.path.join(os.getcwd(), 'th-dataset')
    file_list = os.listdir(data_dir)
    for file in file_list:
        filename = os.path.join(data_dir, file)
        file_id = os.path.splitext(file)[0]
        with open(filename, encoding="utf-8") as f:
            words = f.read().lower().split()
            for word in words:
                if word[-1] in ignore_char:
                    word = word[:-1]
                word.replace(''.join(ignore_char), "")
                if word not in stop_words:
                    word = word.strip('1234567890-\'.“!@#$%^&*(){[",./:;<>')
                    if word:
                        invIdx.add_entry((word, file_id))

    return invIdx

# writing the inverted index posting list to the output file
def writeFile(invIdx):
    with open('output.txt', 'w', encoding="utf-8") as f:
        for word, files in invIdx.entries():
            f.write(word + "(" + f"{len(files)}" + ') ')
            data = dict(Counter(files))
            for doc, freq in data.items():
                f.write(f' {{{doc}:{freq}}} ')
            f.write('\n')


writeFile(createDictionary())
