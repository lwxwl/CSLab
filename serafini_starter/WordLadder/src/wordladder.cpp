// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "vector.h"
using namespace std;

static bool getEnglishWord(const Lexicon& dictionary, string& word, string prompt);
static bool checkWordEndpoints(const Lexicon& dictionary, const string& sourceWord, string& destinationWord);
static Vector<string> getWordLadder(const Lexicon& dictionary, const string& sourceWord, const string& destinationWord);
static Lexicon oneHopAway(const Lexicon& dictionary, Lexicon& usedWords, const string& topWord);
static void printWordLadder(const Vector<string>& wordLadder, const string& sourceWord, const string& destinationWord);

int main() {
    Lexicon dictionary("dictionary.txt");

    cout << "Welcome to CS 106B Word Ladder." << endl;
    cout << "Please give me two English words, and I will change the" << endl;
    cout << "first into the second by changing one letter at a time." <<endl;
    cout << endl;

    while(true) {
        string sourceWord;
        string destinationWord;
        Vector<string> wordLadder;

        if(getEnglishWord(dictionary, sourceWord, "Word #1 (or Enter to quit): ")) break;
        if(getEnglishWord(dictionary, destinationWord, "Word #2 (or Enter to quit): ")) break;
        if(checkWordEndpoints(dictionary, sourceWord, destinationWord)) break;

        wordLadder = getWordLadder(dictionary, sourceWord, destinationWord);
        printWordLadder(wordLadder, sourceWord, destinationWord);
    }
    cout << "\nHave a nice day." << endl;
    return 0;
}

static bool getEnglishWord(const Lexicon& dictionary, string& word, string prompt) {
    while(true) {
        cout << prompt;
        getline(cin, word);
        if(word.empty()) {
            return true;
        } else if(dictionary.contains(word)) {
            return false;
        }
        cout << "The two words must be found in the dictionary." << endl;
    }
}

static bool checkWordEndpoints(const Lexicon& dictionary, const string& sourceWord, string& destinationWord) {
    if(sourceWord.length() != destinationWord.length()) {
        cout << "The two words must be the same length." << endl;
        return getEnglishWord(dictionary, destinationWord, " ");
    }
    return false;
}


static Vector<string> getWordLadder(const Lexicon& dictionary, const string& sourceWord, const string& destinationWord) {
    Queue< Vector<string> > paths;
    Vector<string> wordLadder;
    Lexicon usedWords;

    wordLadder.add(sourceWord);
    usedWords.add(sourceWord);
    paths.enqueue(wordLadder);
    while(!paths.isEmpty()) {
        wordLadder = paths.dequeue();
        string topWord = wordLadder[wordLadder.size()-1];
        if(topWord == destinationWord) {
            break;
        } else {
            for(string word: oneHopAway(dictionary, usedWords, topWord)) {
                Vector<string> wordLadderClone = wordLadder;
                wordLadderClone.add(word);
                paths.enqueue(wordLadderClone);
            }
        }
    }
    return wordLadder;
}


static Lexicon oneHopAway(const Lexicon& dictionary, Lexicon& usedWords, const string& topWord) {
    Lexicon oneHopAway;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < topWord.length(); i++) {
        for(int j = 0; j < alphabet.length(); j++) {
            string testWord = topWord;
            testWord[i] = alphabet[j];
            if(dictionary.contains(testWord) && !usedWords.contains(testWord)) {
                oneHopAway.add(testWord);
                usedWords.add(testWord);
            }
        }
    }
    return oneHopAway;
}


static void printWordLadder(const Vector<string>& wordLadder, const string& sourceWord, const string& destinationWord) {
    if(sourceWord == destinationWord) {
        cout << "A ladder from " << sourceWord << "back to" <<destinationWord << ".";
        cout << "\n" << wordLadder[0];
    } else if(wordLadder.size() == 1) {
        cout << "No word ladder from " << sourceWord << "back to" << destinationWord << ".";
    } else {
        cout << "A ladder from " << sourceWord << "back to" <<destinationWord << ".";
        for(string word: wordLadder) {
            cout << ' ' << word;
        }
    }
    cout << endl << endl;
}


