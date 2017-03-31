// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"
#include "hashmap.h"
#include "filelib.h"

using namespace std;

static const int STOP_NUMBER = 0;

static void welcome();
static void buildMapNgrams(ifstream& file, HashMap< Vector<string>, Vector<string> >& mapNgrams, const int& numberOfNgrams);
static void readInFile(ifstream& file, Vector<string>& wordsInFile);
static void addKeyValuesToMap(HashMap< Vector<string>, Vector<string> >& mapNgrams, const Vector<string> wordsInFile, const int numberOfNgrams);
static Vector<string> chooseRandomStartingPoint(const HashMap< Vector<string>, Vector<string> >& mapNgrams);
static Vector<string> generateRandomSentence(const HashMap< Vector<string>, Vector<string> >& mapNgrams, const Vector<string>& startKey, const int numberOfNgrams, const int numberOfRandomWords);
static void printRandomSentence(const Vector<string> randomSentence);

int main() {
    ifstream file;
    int numberOfNgrams;
    HashMap< Vector<string>, Vector<string> > mapNgrams;

    cout<<"Welcome to CS 106B Random Writer ('N-Grams')."<< endl;
    cout<<"This program makes random text based on a document."<< endl;
    cout<<"Give me an input file and an 'N' value for groups"<<endl;
    cout<<"of words, and I'll create random text for you."<<'\n';

    promptUserForFile(file, "Input file name? ");
    while(true) {
        numberOfNgrams = getInteger("Value of N? ");
        if(numberOfNgrams > STOP_NUMBER) break;
        cout << "N must be 1 or greater." << endl;
    }
    buildMapNgrams(file, mapNgrams, numberOfNgrams);
    while(true) {
        int numberOfRandomWords = getInteger("\n# of random words to generate (0 to quit)? ");
        if(numberOfRandomWords <= STOP_NUMBER) break;
        Vector<string> startKey = chooseRandomStartingPoint(mapNgrams);
        Vector<string> randomSentence = generateRandomSentence(mapNgrams, startKey, numberOfNgrams, numberOfRandomWords);
        printRandomSentence(randomSentence);
    }
    cout << "Exiting." << endl;
    return 0;
}

static void buildMapNgrams(ifstream& file, HashMap< Vector<string>, Vector<string> >& mapNgrams, const int& numberOfNgrams) {
    Vector<string> wordsInFile;
    readInFile(file, wordsInFile);
    addKeyValuesToMap(mapNgrams, wordsInFile, numberOfNgrams);
}

static void readInFile(ifstream& file, Vector<string>& wordsInFile) {
    string value;
    while(file >> value) {
        wordsInFile.add(value);
    }
    file.close();
}

static void addKeyValuesToMap(HashMap< Vector<string>, Vector<string> >& mapNgrams, const Vector<string> wordsInFile, const int numberOfNgrams) {
    for(int wordNumber = 0; wordNumber < wordsInFile.size(); wordNumber++) {
        Vector<string> mapKeys;
        Vector<string> mapValues;

        for(int indexNgram = 0; indexNgram < numberOfNgrams - 1; indexNgram++) {
            int keyInFile = (wordNumber + indexNgram) % wordsInFile.size();
            mapKeys.add(wordsInFile[keyInFile]);
        }
        int valueInFile = (wordNumber + (numberOfNgrams - 1)) % wordsInFile.size();
        if(mapNgrams.containsKey(mapKeys)) {
            mapValues = mapNgrams.get(mapKeys);
        }
        mapValues.add(wordsInFile[valueInFile]);
        mapNgrams.put(mapKeys, mapValues);
    }
}

static Vector<string> chooseRandomStartingPoint(const HashMap< Vector<string>, Vector<string> >& mapNgrams) {
    Vector<string> startKey;
    int counter = 0;
    int randomNumber = randomInteger(0, mapNgrams.size() - 1);
    for(Vector<string> i: mapNgrams) {
        counter++;
        if(counter == randomNumber) {
            startKey = i;
            break;
        }
    }
    return startKey;
}

static Vector<string> generateRandomSentence(const HashMap< Vector<string>, Vector<string> >& mapNgrams,
                                            const Vector<string>& startKey, const int numberOfNgrams, const int numberOfRandomWords) {
    int numberOfWordsGenerated = startKey.size();
    Vector<string> randomSentence = startKey;
    while(numberOfWordsGenerated < numberOfRandomWords) {
        Vector<string> currentWindow;
        for(int i = 0; i < numberOfNgrams - 1; i++) {
            string currentWord = randomSentence[numberOfWordsGenerated - (numberOfNgrams - 1) + i];
            currentWindow.add(currentWord);
        }
        Vector<string> possibleNextWords = mapNgrams.get(currentWindow);
        string nextWord = possibleNextWords[randomInteger(0, possibleNextWords.size() - 1)];
        randomSentence.add(nextWord);
        numberOfWordsGenerated++;
    }
    return randomSentence;
}

static void printRandomSentence(const Vector<string> randomSentence) {
    cout << "...";
    for(string word: randomSentence) {
        cout << ' ' << word;
    }
    cout << "..." << endl;
}
