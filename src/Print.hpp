#pragma once

#include <cmath>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include "Buffer.hpp"
#include "WordData.hpp"

using namespace std;

int getDistance(int previous, int current) {
  int prevNumDigits = to_string(previous).length();
  int currentNumDigits = to_string(current).length();

  if (prevNumDigits == currentNumDigits) {
    int diff = current - previous;
    return diff == 0 ? 0 : diff + (diff * currentNumDigits) - 1;
  }

  int sum = 0;
  for (int i = currentNumDigits; i > prevNumDigits; i--) {
    int base = pow(10, i - 1);
    sum += getDistance(base, current);
    sum += (current == base) ? i + 1 : i + 2;
    current = base - 1;

    return sum + getDistance(previous, current);
  }

  return 0;
}

void printCrossReference(map<string, WordData>& collection,
                         int numLines,
                         const string& filePath) {
  stringstream buffer;

  buffer << left << setw(15) << "word";
  for (int i = 0; i < numLines; i++) {
    buffer << (i + 1) << " ";
  }

  buffer << endl << string(15 + numLines * 3, '-') << endl;

  for (auto key : collection) {
    if (key.second.count > 1) {
      buffer << left << setw(14) << key.first;

      for (int i = 0; i < key.second.lineIndices.size(); i++) {
        int prevIndex = (i == 0) ? 0 : key.second.lineIndices[i - 1] + 1;
        int lineIndex = key.second.lineIndices[i] + 1;

        int distance = getDistance(prevIndex, lineIndex);
        buffer << string(distance, ' ') << "*";
      }

      buffer << endl;
    }
  }

  saveToBuffer(filePath, buffer);
}

void printURLs(vector<string>& urls, const string& filePath) {
  stringstream buffer;
  for (string url : urls) {
    buffer << url << endl;
  }
  saveToBuffer(filePath, buffer);
}

void printWordCount(map<string, WordData>& collection, const string& filePath) {
  stringstream buffer;

  buffer << left << setw(15) << "word"
         << "count" << endl;

  buffer << string(20, '-') << endl;

  for (auto key : collection) {
    if (key.second.count > 1) {
      buffer << left << setw(15) << key.first << key.second.count << endl;
    }
  }

  saveToBuffer(filePath, buffer);
}
