//Joseph Timm
//CS3100
//Project 5 - Alphabet Trie
//this file contains the actual functions of the Trie

#include "trie.h"
#define LETTERSIZE 26

//trie constructor for new trie with a root node and nothing else  
Trie:: Trie():
    nodeCount(1), //starting at 1 node for our root node
    wordCount(0)
{
    root = new trieNode();
};  

Trie:: ~Trie(){
    recurseDelete(root); 
    delete root; //make sure to delete the root
    wordCount=0; //reset word count
    //this method will eventually get our node count to 0 so we dont need to adjust it in here
};

void Trie:: recurseDelete(trieNode* current){
    for (int i=0; i<LETTERSIZE; i++){ //pan through array  
        if (current->letters[i] != nullptr){ //if spot in array is not null then call recurse delete on that node 
            recurseDelete(current->letters[i]);
        }
    }
    delete current; //since it made it out the for loop, all the pointers in this letters array are dull so the node can be deleted
    nodeCount--; //decrement total node count since a node was just deleted
    return;
}

Trie:: Trie(const Trie& other){
    nodeCount=other.nodeCount;
    wordCount=other.wordCount;
    root = recurseCopy(other.root);
}; 

bool Trie::insert(string s){
    if (find(s)){ //need to first check if word is already there and if so return false since it wont be added
        return false;
    } else {
        trieNode* current = root;
        for (int i=0; i<s.length(); i++){
            int index = s[i] - 'a'; //get the ascii value of the ith letter of the word and subtract ascii a to get an index value 
            if (current->letters[index] == nullptr){ //if that index value is empty, make a new node to point to 
                trieNode* newNode = new trieNode(); //make new node
                nodeCount++; //increment total node count
                current->letters[index]=newNode; //set that index to point to the new node     
            }
            current = current->letters[index]; //move current to the new node that was created(or that index if there is already node there)
        }
        current->endWord=true; //make sure to set this node as being the end of a word
        wordCount++; //make sure to increase word count
        return true; //return true since word was succesfully inserted   
    }
}

int Trie::count(){
    return wordCount;
}

int Trie::getSize(){
    return nodeCount;
}

bool Trie::find(string s){
    trieNode* current = root;
    for (int i=0; i<s.length(); i++){
        int index = s[i] - 'a'; //get index value for the current position of the string
        if (current->letters[index]==nullptr){
            return false; //if current letter doesnt have a pointer the word wont be found so exit
        } else if (i==s.length()-1 && current->letters[index]->endWord==true) {   // length -1 since i starts at 0
            //since the node that the is being pointed to has endWord value need to go into that node to check
            return true; //if its gotten to this point and endWord is true then the word is found
        } else{
            current=current->letters[index]; //if word still exists and isnt ending on current letter go to next letter of word
        }
    }
    return false;
}

int Trie::completeCount(string s){
    int count = 0;
    trieNode* current = root;
    for (int i=0; i<s.length(); i++){ //for loop to start recurse call at the end of the string entered
        int index = s[i] - 'a'; //get index value for the current position of the string
        if (current->letters[index]==nullptr){
            return 0; //no words will exist 
        } else{
            current=current->letters[index]; //follow node
        }
    }
    if (current->endWord==true){ //check if the string itself is a word and increase count if so
        count++; 
    }
    count = completeCountHelper(s, current, count); //start recurse call
    return count;

}

int Trie:: completeCountHelper(string s, trieNode* current, int count){
    for (int i=0; i<LETTERSIZE; i++){ //loop through initial nodes array
        if (current->letters[i] != nullptr){
            if (current->letters[i]->endWord==true){ //since end of word will be a value of where that node is pointing have to check inside of it
                count++; //increases the count on this stack frame. 
                //COMMENTS BELOW MORE SO FOR ME TO UNDERSTAND
                    //since this updated count is being returned at the end of the function, passed to additional calls, 
                    //and being set equal to the call it will make sure it stays consistent throughout the recurrsion process. 
                    //Important part is that it is being set equal to the recurse call or else the count would not be updated upon returning 
                    //from the recurse call since it is just a call without putting that return value into anything
            } 
        count=completeCountHelper(s, current->letters[i], count); //then recurse call on that pointer to check if it keeps going
        }
    }
    return count; //once making it this far, array has all null pointers so return the count
}

vector<string> Trie::complete(string s){
    vector<string> wordList;
    trieNode* current = root;
    for (int i=0; i<s.length(); i++){ //for loop to start recurse call at the end of the string entered
        int index = s[i] - 'a'; //get index value for the current position of the string
        if (current->letters[index]==nullptr){
            return wordList; //no words will exist 
        } else{
            current=current->letters[index]; //follow node
        }
    }
    if (current->endWord==true){ //check if the string itself is a word and add word to the vector
        wordList.push_back(s);
    }
    wordList = completeHelper(s, current, wordList); //start recurse call
    return wordList;
}

vector<string> Trie:: completeHelper(string s, trieNode* current, vector<string> wordList){
    for (int i=0; i<LETTERSIZE; i++){ //loop through initial nodes array
        if (current->letters[i] != nullptr){
            char newLetter = (char) i + 'a'; //get char version of whatever the letter that has a pointer in it is
            if (current->letters[i]->endWord==true){ //since end of word will be a value of where that node is pointing have to check inside of it
                wordList.push_back(s+newLetter);
            } 
        wordList=completeHelper((s+newLetter), current->letters[i], wordList); //then recurse call on that pointer to check if it keeps going
        }
    }
    return wordList; //once making it this far, array has all null pointers so return the count
}


Trie& Trie::operator=(const Trie& other){
    //first get rid of everything in the trie being called on
    recurseDelete(root); 
    delete root; //make sure to delete the root
    nodeCount=other.nodeCount;
    wordCount=other.wordCount;
   root = recurseCopy(other.root);

}

Trie::trieNode* Trie:: recurseCopy(trieNode* copyFrom){
    for (int i=0; i<LETTERSIZE; i++){ //pan through array  
        if (copyFrom->letters[i] != nullptr){ //if spot in array is not null then call recurse copy on that node 
            recurseCopy(copyFrom->letters[i]); 
        }
    }
    trieNode* newNode = new trieNode(); //make new node
    return newNode;

}
