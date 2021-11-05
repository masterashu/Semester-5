Inverted Index

Approach:
* Reading the files from the dataset
* Here we are using pickle files to store the Inverted Index on the secondary memory
- pickle files are binaries that store the data/object after serialization and can be read again, thus highly reducing the space complexity
* The pickle files are created storing the Inverted Index, with the index file storing the keys of the first and the last word of each file

files:
Inverted_Index.py : main code
split_dict.py : code for creating the inv index
stop_words.py : list of stop words
data/ : generated pickle files
--
Ketan Lambat
S20180010081