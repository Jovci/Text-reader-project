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

  bool isEndPunctuation(const char& character);

  vector<string> getValues(const string& key);

  bool search(const string& key);

  size_t howManyfollowers(const string& key);

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