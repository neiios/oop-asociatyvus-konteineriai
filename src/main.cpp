#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include "Buffer.hpp"
#include "Print.hpp"
#include "WordData.hpp"

#define NON_WORD_PATTERN "[-.%,?!/;:\"'()\\]\\[*0-9]"
#define URL_PATTERN                                     \
  "(((http|https)://)?www\\.)?[a-zA-Z0-9@:%._\\+~#?&//" \
  "=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)|"  // match every
                                                              // word that has
                                                              // at inside
                                                              // "\\b(?=\\w*at)\\w+\\b"

using namespace std;

string toLowerCase(string& word) {
  for_each(word.begin(), word.end(), [](char& c) { c = tolower(c); });
  return word;
}

int main() {
  string filePath = "source.txt";

  vector<string> urls;
  map<string, WordData> collection;

  // place the file into the buffer
  stringstream buffer = getBuffer(filePath);

  // line index incremented in the while loop
  int lineIndex = 0;
  // holds a line from a text file
  string line;
  while (getline(buffer, line)) {
    // use istringstream to read each line
    istringstream iss(line);
    string word;
    while (iss >> word) {
      // if string is a url add it to the urls vector
      if (regex_match(word, regex(URL_PATTERN))) {
        urls.push_back(word);
      } else {
        word = regex_replace(word, regex(NON_WORD_PATTERN), "");
        addWordToCollection(toLowerCase(word), collection, lineIndex);
      }
    }

    lineIndex++;
  }

  printCrossReference(collection, lineIndex, "cross-reference.txt");
  printURLs(urls, "urls.txt");
  printWordCount(collection, "word-count.txt");

  cout << string(40, '-') << "\nThe program has finished successfully!\n"
       << string(40, '-') << "\n";
  return 0;
}
