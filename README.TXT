Work is done in TextReader.hpp
Program opens up the given file and read in a single word at a time, then "sanitizes" it (remove some non-alphabetic characters like dashes, slashes, etc.). Form key, value associations so that each word has its following words in a vector. For example, for the last word in a sentence: If it ends with punctuation: i. Separate the end punctuation from the word. ii. Store the second last word as a key, and add to the value, the last word without the end punctuation. iii. You will then need to store the last word you read in without the end punctuation as a key, and add the punctuation to the value. Finally make sure that any end punctuation as a key has an associated following value of $ After you have read_in the complete txt input file, you should have a key representing each unique word in the file. The corresponding value for a key, will be a vector of all the words that have immediately followed this word


Project 4
Individually
John Morkovci
jovci@csu.fullerton.edu
