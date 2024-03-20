//Joseph Timm
//CS3100
//Project 5 - Alphabet Trie
//this function contains the function declarations and member data for both the Trie and trieNodes

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Trie{

    private:
        class trieNode {

            public: 
            trieNode* letters[26]; //size 26 array for all 26 letters 
            bool endWord;

            trieNode(): endWord(nullptr){ //constructor 
                for (int i=0; i<26; i++){ //less than 26 for size of array 
                    letters[i]=nullptr;
                }
            } 

            ~trieNode(){} //destructor
        };

    public:
       
        Trie();  //constuctor

        ~Trie(); //destructor

        Trie(const Trie& other); //copy constructor

        bool insert(string s);
            //Insert a new word into the trie. Duplicate words are not allowed. 
            //This function should return true if the word is successfully inserted into the trie, and false if the word could not be inserted 
            //(for example, due to a duplicate word already found in the trie).

        int count();
            //return the number of words in the trie

        int getSize();
            //return the total number of nodes in the trie

        bool find(string s);
            // if the given word is found in the trie, this function should return true, otherwise this function should return false

        int completeCount(string s);
            //this function should return the number of words in the dictionary that begin with the given input string. 
            //If no matching words are found, the function should return zero.

        vector<string> complete(string s);
            //this function should return a vector of strings containing all of the words in the dictionary that begin with the given input string
            //For each word found in the trie, there will be one value in the vector. 
            //If no matching words are found, the function should return an empty vector.


        Trie& operator=(const Trie& other);
            //should remove all contents of trie1 (without memory leaks) and make an independent copy of trie2 in trie1.

        //Member data for Trie
        int nodeCount;
        int wordCount;
        trieNode* root;


        //CUSTOM FUNCTIONS
        void  recurseDelete(trieNode* current);

        trieNode* recurseCopy(trieNode* copyFrom);

        int completeCountHelper(string s, trieNode* current, int count);

        vector<string> completeHelper(string s, trieNode* current, vector<string> wordList);

};