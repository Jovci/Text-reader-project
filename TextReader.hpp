#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "sanitize.hpp"

using namespace std;

class TextReader {
 private:
  map<string, vector<string>> wordFollowers;

 public:
  void readIn(const string& filename);
  /*This should open up the given file and read in a single word at a time,
     "sanitize" it (remove some non-alphabetic characters like dashes, slashes,
     etc.). Form key, value associations so that each word has its following
     words in a vector. For example, for the last word in a sentence: If it ends
     with punctuation: i. Separate the end punctuation from the word. ii. Store
     the second last word as a key, and add to the value, the last word without
     the end punctuation. iii. You will then need to store the last word you
     read in without the end punctuation as a key, and add the punctuation to
     the value. Finally make sure that any end punctuation as a key has an
     associated following value of $ After you have read_in the complete txt
     input file, you should have a key representing each unique word in the
     file. The corresponding value for a key, will be a vector of all the words
     that have immediately followed this word
*/
  bool isEndPunctuation(
      const char& character);  // return true if the given char is one of the
                               // following: . ? !

  vector<string> getValues(
      const string& key);  // return the vector of words following a given key

  bool search(const string& key);  // return true if the given key is found,
                                   // else it should return false.

  size_t howManyfollowers(
      const string& key);  // return the count of words that follow the given
                           // word in the text.

  void insert(const string& key, const string& newValue);
};

//  TO DO

//  COMPLETE THE FOLLOWING FUNCTIONS

void TextReader::readIn(const string& filename) {
  ifstream myfile;
  myfile.open(filename);
  if (myfile.is_open()) {
    string oldWord = "^";
    string newWord;

    while (myfile >> newWord) {
      sanitize(newWord);
      if (!newWord.empty()) {
        if (isEndPunctuation(newWord.back())) {
          string punc;
          punc.push_back(oldWord.back());
          string firstpart = newWord.substr(0, newWord.size() - 1);

          insert(oldWord, firstpart);
          insert(firstpart, punc);
          insert(punc, "$");

          oldWord = "^";
        } else {
          insert(oldWord, newWord);
          oldWord = newWord;
        }
      }
    }
    myfile.close();
  } else
    cout << "Error in opening file: " << filename << endl;
}

void TextReader::insert(const string& key, const string& newValue) {
  vector<string> newVector;
  if (search(key)) newVector = getValues(key);
  newVector.push_back(newValue);
  wordFollowers[key] = newVector;
}

bool TextReader::isEndPunctuation(const char& character) {
  if (character == '!' || character == '?' || character == '.')
    return true;
  else
    return false;
}

vector<string> TextReader::getValues(const string& key) {
  return wordFollowers.find(key)->second;
}

bool TextReader::search(const string& key) {
  if (wordFollowers.find(key) != wordFollowers.end())
    return true;
  else
    return false;
}

size_t TextReader::howManyfollowers(const string& key) {
  size_t followers = 0;
  if (search(key)) {
    followers = getValues(key).size();
  }
  return followers;
}