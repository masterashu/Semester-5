# %%
from collections import defaultdict
 
def MyDict():
    return defaultdict(MyDict)

class Trie:
    alphabet = 'qwertyuiopasdfghjklzxcvbnm'
    
    def __init__(self):
        self.data = defaultdict(MyDict)

    def load(self, filename='dictionary.txt'):
        with open(filename, 'r') as words:
            for word in words.readlines():
                self.add_word(word.strip())
        
    def add_word(self, word):
        data = self.data
        for ch in word:
            data = data[ch]
        data['$'] = True

    def find(self, word, matched=None, data=None, count=2, matches=None):
        if matches is None:
            matches = set()
        data = data or self.data
        matched = matched or ''

        # standard matching
        if count == 0:
            if self._search(data, word):
                matches.add(matched + word)
            return
        
        if len(word) == 0:
            if self._search(data, word):
                matches.add(matched + word)
            
            # if count > 0:
                # for ch in self.alphabet:
                #     if self._search(data, word + ch):
                #         matches.add(matched + ch)
            return

        # changed
        _, word2 = word[0], word[1:]
        for ch in self.alphabet:
            if ch not in data:
                continue
            if ch == word[0]:
                self.find(word2, matched+ch, data[ch], count=count,matches=matches)
            else:
                self.find(word2, matched+ch, data[ch], count=count-1,matches=matches)
        
        # missing
        word2 = word[0] + word[1:]
        for ch in self.alphabet:
            if ch not in data:
                continue
            self.find(word2, matched+ch, data[ch], count=count-1,matches=matches)
        
        # extra
        if len(word) >= 1:
            _, word2 = word[0], word2[1:]
            self.find(word2, matched, data, count=count-1,matches=matches)

        return matches

    def _search(self, data, word):
        if not word:
            return data['$'] or False
            
        ch, word2 = word[0], word[1:]

        if ch not in data:
            return False

        return self._search(data[ch], word2)






# %%
if __name__ == "__main__":
    t = Trie()
    t.load()
    print(t.find('hello', count=1))
