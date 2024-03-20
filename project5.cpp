//Joseph Timm
//CS3100
//Project 5 - Alphabet Trie

#include "trie.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream> // fstream for file stream objects 
using namespace std;

//This file contains the autocomplete program that will read in a prefix and print out all the words that begin with that prefix
int main(){

    //read in file
    ifstream fileIN("wordlist.txt");
    vector<string> wordlist;
    if (fileIN.good()) {
        string word;
        while (!fileIN.eof()){
            fileIN>>word;
            wordlist.push_back(word);
        }
    } else{
        cerr << "Couldn't open file." << endl;
    }

    //make new trie and input all the words into it 
    Trie allWords;
    for(auto word: wordlist){
        allWords.insert(word);
    }
    
    //get user input
    cout << "Please enter a word or prefix: ";
    string inputWord; //initialize input variable
    cin >> inputWord; //put user input into the word
    cout << "There are " << allWords.completeCount(inputWord) << " completions for the prefix '" << inputWord << "'. Show completions? ";
    string showCompletions;
    cin >> showCompletions;

    //output all words
    if (showCompletions=="yes") {  
        vector<string> completedWords = allWords.complete(inputWord);
        cout << "Completions" << endl;
        cout << "-----------" << endl;
        for (int i=0; i<completedWords.size(); i++){
            cout <<completedWords[i] << endl;
        }
    }

}