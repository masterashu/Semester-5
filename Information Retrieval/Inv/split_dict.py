from typing import List, Dict, Tuple
import pickle
import os


class SplitDict:
    # max number of words that can be present in a page
    PAGE_ENTRY = 80

    def __init__(self):
        self.index_file = open(os.path.join('data', 'index.P'), 'w')
        self.data_files = dict()
        fname = os.path.join('data', f'{len(self.data_files)}.P')
        with open(fname, 'wb') as f:
            pickle.dump({}, f, protocol=pickle.HIGHEST_PROTOCOL)
            self.data_files['a'] = fname

    # function to add an word into the index
    def add_entry(self, data: Tuple[str, str]):
        word, doc = data
        fname = self.get_file(word)
        page: Dict[str, List[str]] = self.load_page(fname)
        # if word exists in idx, append the doc id
        if word in page:
            page[word].append(doc)
        else:
            # create a posting list
            page[word] = [doc]
            # if cnt of words exced page limit, create a new page (pickle file)
            if len(page) > self.PAGE_ENTRY - 1:
                sorted_page = sorted(page.items(), key=lambda kv: kv[0])
                new_page = {
                    key: value for key, value in sorted_page[(len(sorted_page) // 2):]
                }
                page = {
                    key: value for key, value in sorted_page[:(len(sorted_page) // 2)]
                }
                new_file = os.path.join('data', f'{len(self.data_files)}.P')
                self.data_files[min(new_page.keys())] = new_file
                # writing the contents to the pickle file
                with open(new_file, 'wb') as nf:
                    pickle.dump(new_page, nf, protocol=pickle.HIGHEST_PROTOCOL)

        with open(fname, 'wb') as f:
            pickle.dump(page, f, protocol=pickle.HIGHEST_PROTOCOL)

    def get_file(self, word: str):
        try:
            keys = list(filter(lambda x: x <= word, self.data_files.keys()))
            return self.data_files[max(keys)]
        except:
            print(word, keys)
            raise ValueError()

    # returns the inv idx and posting list
    def entries(self):
        files = sorted(self.data_files.items(), key=lambda kv: kv[1])
        for _, filename in files:
            page = self.load_page(filename)
            page_entries = sorted(page.items(), key=lambda kv: kv[0])
            for word_entries in page_entries:
                yield word_entries

    # loading the pickle file
    def load_page(self, filename):
        page = {}
        with open(filename, 'rb') as datafile:
            page = pickle.load(datafile)
        return page

# if __name__ == "__main__":
#     sd = SplitDict()
#     with open("testfile.txt", encoding="utf-8") as f:
#         words = f.read().lower().split()
#         for word in words:
#             if word not in stop_words:
#                 word = word.strip('1234567890')
#                 sd.add_entry((word, str(random.randint(1, 6))))
#
#     with open('words_dict2.txt', 'w', encoding="utf-8") as f:
#         from collections import Counter
#         for word, files in sd.entries():
#             f.write(word + "(" + f"{len(files)}" + ') ')
#             data = dict(Counter(files))
#             for doc, freq in data.items():
#                 f.write(f' {{{doc}:{freq}}} ')
#             f.write('\n')
