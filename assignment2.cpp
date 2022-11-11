
#include <iostream>
#include <fstream> //libray for providing functions for files
#include <string>
#include <stack>//library for stack
#include <vector>//libarary to allow variables to chane the direction of characters
#include <queue>//libary for queque
#include <set>//library for making each variable unique to avoid duplication

using namespace std;

void getWords(string &firstelement, string &secondelement);
void printWordLadder(string firstelement, string secondelement); 
int main() {
    
  string firstelement, secondelement;
  getWords(firstelement, secondelement); 
  printWordLadder(firstelement, secondelement);
    
  return 0;
}
//function that will ask user to input two words and store them in function parameters
void getWords(string &firstword, string &secondword) {
  while (true) {
    cout << " Enter first word: ";
    cin>>firstword;
    
    cout << " Enter second word of the same length: ";
    cin>>secondword;
    
    if (firstword.length() == secondword.length()) {
      break;
    }
    cout << " Enter two words with the same length." << endl;
  }
}
 
//in this function we have two parameters and to specify and show the connection of words
void printWordLadder(string firstword, string secondword){ 

    queue<stack<string> > myQueue;    //we need to create an empty queue of stacks  
    stack<string> wordladder;                          //the stack we're creating will contain the lastword
    
    stack<string> myStack;   /* here we create and add in our stack to the queue and
	                            ofcourse should contain first word*/
    myStack.push(firstword);
    myQueue.push(myStack);
    
    //we're going to create two set , one will be for englishWords and other one for tested
    string token;
    ifstream englishWords("EnglishWords.txt");
    set<string> myEnglishWord;
    set<string> testedWords;
    
    //if stream is associated to Englishwords
    if(englishWords.is_open()) {
      
	      while (englishWords >> token) {
	    	myEnglishWord.insert(token);
	      }
	      
	      // while the queue is not empty:
	      while (!(myQueue.empty())) {
	        
	        // dequeue the partial-ladder stack from the front of the queue.
			stack<string> ladder = myQueue.front();
			myQueue.pop();
			string word = ladder.top();
		        
			// if the word on top of the stack is the  word we are looking for:
			if (word == secondword) {
			
			  //  then the solution is the elements of the stack and display it!
			  cout << "The ladder from " << firstword << " to " << secondword << " is \n";
			 
			  //Copy the ladder stack to worldladder to take it in the order.
			  
			  while(!ladder.empty()){
			  	wordladder.push(ladder.top());
			  	ladder.pop();
			  }
			  while(!wordladder.empty()){
			  	cout<<wordladder.top()<<" > ";
			  	wordladder.pop();
			  }
		} 
		else {
			  // for each valid English word that is a close  to the word on top of the stack:
			  string test;
			  for (int i = 0; i < word.size(); i++) {
			    for (char j = 'a'; j <= 'z'; j++) {
			    test = word.substr(0, i) + j + word.substr(i + 1);
		            
			    // if that word is valid
			    if (myEnglishWord.count(test)) {
			      
			      //if we have not used that close word before
			      if (!testedWords.count(test)) {
				
						// create a copy of the current ladder stack.
						stack<string> copy = ladder;
				                
						// put the close word on top of the copy stack.
						copy.push(test);
				                
						// we are adding  the copy stack to the end of the queue.
						myQueue.push(copy);
			      }
			    }
		            
			    // Add test to tested words because it is already used.
			    testedWords.insert(test);
			}
		}
	      }
	    }
    } else {
      cerr << "Couldn't open the englishWords" << endl;
    }
    
    
}

