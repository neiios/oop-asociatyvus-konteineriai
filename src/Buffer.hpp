#pragma once

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include "WordData.hpp"

using namespace std;

void addWordToCollection(const string& word,
                         map<string, WordData>& collection,
                         const int& lineIndex) {
  if (word.empty()) {
    return;
  }

  auto wordIt = collection.find(word);

  if (wordIt == collection.end()) {
    collection.insert({word, WordData(lineIndex)});
  } else {
    if (lineIndex != wordIt->second.lineIndices.back()) {
      wordIt->second.lineIndices.push_back(lineIndex);
    }

    wordIt->second.count++;
  }
}

stringstream getBuffer(const string& filePath) {
  ifstream file;
  file.open(filePath);

  if (!file) {
    throw std::runtime_error("Error: file \"" + filePath +
                             "\" could not be opened");
  }

  stringstream buffer;
  buffer << file.rdbuf();
  file.close();

  return buffer;
}

void saveToBuffer(const string& filePath, stringstream& buffer) {
  std::ofstream file;
  file.open(filePath);

  if (!file) {
    throw std::runtime_error("Error: file \"" + filePath +
                             "\" could not be opened");
  }

  file << buffer.str();
  file.close();
}
