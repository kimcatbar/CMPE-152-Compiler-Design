//
//  main.cpp
//  CMPE-152 Scanner Assignment#2
//
//  Created by Kimberly Manzano on 2/6/23.
//

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

enum Token {
    //and = "AND", ......, *) = "RCOMMENT"
    //and so on until the end
};

class Scanner {
    public:
    string nexttoken();//function to access next char in input file
    private:
    
    vector<string> in_stream; //vector to store input stream
};

int main(int argc, const char * argv[]) {
    //feed text file
    std::cout << "Hello, World!\n";
    //if its a space, we keep going
    
    //if it is a A-Z or a-z, state = 2: word
    
    //if space after a word, look up token/label pair and output
    
    //if it 0-9, state = 3: number
    //get number until space is detected
    //look up token word: integer, real, etc
    
    //if +,-,/,*, or comparison operator, state =4
    //special cases: >=, <= are special symbols
    
    //cout label for each token found 
    return 0;
}
