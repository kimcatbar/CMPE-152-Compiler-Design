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
#include <fstream>



using namespace std;
//Create an enumerated type to represent the token labels
enum class TokenType {
    AND,
    ARRAY,
    ASM,
    BEGIN,
    BREAK,
    CASE,
    CONST,
    CONSTRUCTOR,
    CONTINUE,
    DESTRUCTOR,
    DIV,
    DO,
    DOWNTO,
    ELSE,
    END,
    FALSE,
    FILE,
    FOR,
    FUNCTION,
    GOTO,
    IF,
    IMPLEMENTATION,
    IN,
    INLINE,
    INTERFACE,
    LABEL,
    MOD,
    NIL,
    NOT,
    OBJECT,
    OF,
    ON,
    OPERATOR,
    OR,
    PACKED,
    PROCEDURE,
    PROGRAM,
    RECORD,
    REPEAT,
    SET,
    SHL,
    SHR,
    STRING,
    THEN,
    TO,
    TRUE,
    TYPE,
    UNIT,
    UNTIL,
    USES,
    VAR,
    WHILE,
    WITH,
    XOR,
    INTEGER,
    REAL,
    INDENTIFIER,
    PLUSOP,
    MINUSOP,
    MULTOP,
    DIVOP,
    ASSIGN,
    EQUAL,
    NE,
    LTEQ,
    GTEQ,
    LT,
    GT,
    PLUSEQUAL,
    MINUSEQUAL,
    MULTEQUAL,
    DIVEQUAL,
    CARAT,
    SEMICOLON,
    COMMA,
    LPAREN,
    RPAREN,
    LBRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,
    LCOMMENT,
    RCOMMENT,
    //EOF
};

class Scanner {
    public:
    Scanner() {
        /* set up possible input word as key, and tokentype as value */
        keyword["and"] = TokenType::AND;
        keyword["array"] = TokenType::ARRAY;
        keyword["asm"] = TokenType::ASM;
        keyword["begin"] = TokenType::BEGIN;
        keyword["break"] = TokenType::BREAK;
        keyword["case"] = TokenType::CASE;
        keyword["const"] = TokenType::CONST;
        keyword["constructor"] = TokenType::CONSTRUCTOR;
        keyword["continue"] = TokenType::CONTINUE;
        keyword["destructor"] = TokenType::DESTRUCTOR;
        keyword["div"] = TokenType::DIV;
        keyword["do"] = TokenType::DO;
        keyword["downto"] = TokenType::DOWNTO;
        keyword["else"] = TokenType::ELSE;
        keyword["end"] = TokenType::END;
        keyword["FALSE"] = TokenType::FALSE;
        keyword["file"] = TokenType::FILE;
        keyword["for"] = TokenType::FOR;
        keyword["function"] = TokenType::FUNCTION;
        keyword["goto"] = TokenType::GOTO;
        keyword["if"] = TokenType::IF;
        keyword["implementation"] = TokenType::IMPLEMENTATION;
        keyword["in"] = TokenType::IN;
        keyword["inline"] = TokenType::INLINE;
        keyword["interface"] = TokenType::INTERFACE;
        keyword["label"] = TokenType::LABEL;
        keyword["mod"] = TokenType::MOD;
        keyword["nil"] = TokenType::NIL;
        keyword["not"]= TokenType::NOT;
        keyword["object"] = TokenType::OBJECT;
        keyword["of"] = TokenType::OF;
        keyword["on"] = TokenType::ON;
        keyword["operator"] = TokenType::OPERATOR;
        keyword["or"] = TokenType::OR;
        keyword["packed"] = TokenType::PACKED;
        keyword["procedure"] = TokenType::PROCEDURE;
        keyword["program"] = TokenType::PROGRAM;
        keyword["record"] = TokenType::RECORD;
        keyword["repeat"] = TokenType::REPEAT;
        keyword["set"] = TokenType::SET;
        keyword["shl"] = TokenType::SHL;
        keyword["SHR"] = TokenType::SHR;
        keyword["string"] = TokenType::STRING;
        keyword["then"] = TokenType::THEN;
        keyword["to"] = TokenType::TO;
        keyword["TRUE"] = TokenType::TRUE;
        keyword["type"] = TokenType::TYPE;
        keyword["unit"] = TokenType::UNIT;
        keyword["until"] = TokenType::UNTIL;
        keyword["uses"] = TokenType::USES;
        keyword["var"] = TokenType::VAR;
        keyword["while"] = TokenType::WHILE;
        keyword["with"] = TokenType::WITH;
        keyword["xor"] = TokenType::XOR;
        keyword["(integer)"] = TokenType::INTEGER;
        keyword["(real number)"] = TokenType::REAL;
        keyword["(identifier)"] = TokenType::INDENTIFIER;
        keyword["+"] = TokenType::PLUSOP;
        keyword["-"] = TokenType::MINUSOP;
        keyword["*"] = TokenType::MULTOP;
        keyword["/"] = TokenType::DIVOP;
        keyword[":="] = TokenType::ASSIGN;
        keyword["="] = TokenType::EQUAL;
        keyword["<>"] = TokenType::NE;
        keyword["<="] = TokenType::LTEQ;
        keyword[">="] = TokenType::GTEQ;
        keyword["<"] = TokenType::LT;
        keyword[">"] = TokenType::GT;
        keyword["+="] = TokenType::PLUSEQUAL;
        keyword["-=]"] = TokenType::MINUSEQUAL;
        keyword["*="] = TokenType::MULTEQUAL;
        keyword["/="] = TokenType::DIVEQUAL;
        keyword["^"] = TokenType::CARAT;
        keyword[";"] = TokenType::SEMICOLON;
        keyword[","] = TokenType::COMMA;
        keyword["("] = TokenType::LPAREN;
        keyword[")"] = TokenType::RPAREN;
        keyword["["] = TokenType::LBRACKET;
        keyword["]"] = TokenType::RBRACKET;
        keyword["{"] = TokenType::LBRACE;
        keyword["}"] = TokenType::RBRACE;
        keyword["(*"] = TokenType::LCOMMENT;
        keyword["*)"] = TokenType::RCOMMENT;
    }
    Scanner(string input){
        Scanner();
    }
    void processdata(string input){
        unsigned long l = input.length();
        int currentState = 0;
        string currentWord = "";
        string currentNumber = "";
        string currentSymbol = "";
        for (int i = 0; i < l; i++){
            char in = tolower(input[i]);//turn every char to lower case
            if((in >= 'a' && in <= 'z')){//if input at i is a letter state=1
                if(currentState == 3) {//previos char was symbol
                    in_stream.push_back(keyword[currentSymbol]);
                    currentSymbol="";
                }
                currentWord.push_back(in);//add char to token variable
                currentState = 1;//tells is what previous char is
            }
            else if((in >= '0') & (in <= '9')){//if char is a number
                if(currentState == 3){
                    in_stream.push_back(keyword[currentSymbol]);
                    currentSymbol = "";
                }
                if(currentWord == ""){
                    currentNumber.push_back(in);
                }
                else{
                    currentWord.push_back(in);
                }
                currentState = 2;
            }
            else if((in  == '+') || (in == '-') || (in == '*') || (in == '/') || (in == ':') || (in == '=') || (in == '<') || (in == '>') || (in =='^') || (in == ';') || (in == ',') || (in == '(')
                    || (in == ')') || (in == '[') || (in == ']') || (in == '{') || (in == '}')){//if char is special symbol
                if(currentWord != ""){
                    if(keyword.count(currentWord) != 0) {
                        in_stream.push_back(keyword[currentWord]);
                    }
                    else {
                        in_stream.push_back(TokenType::INDENTIFIER);
                    }
                    currentWord = "";
                }
                else if(currentState == 2) {
                    
                    //code
                }
                currentState = 3;
                
            }
            else if((in == ' ') || (in == '\n')){//if spaces detected
                //code
                currentState = 4;
            }
            else {
                cout << "Unrecgonized state/token/symbol." << endl;
            }
                
        }
        cout << "EOF" << endl;
    }
    TokenType nexttoken();//function to access next char in input file
    
    private:
    map<string, TokenType> keyword;
    vector<TokenType> in_stream; //storing tokens after found from input stream
};

int main(int argc, const char * argv[]) {
    //feed text file
    ifstream textfile;
    //change to your own input file
    textfile.open("/Users/kimberlymanzano/Desktop/CMPE-152Assignment#2/CMPE-152 Scanner Assignment#2/CMPE-152 Scanner Assignment#2/sampleinput.txt");
    if (textfile.is_open()){
        cout << "File is open!" << endl;
        string inputtext ="";
        string str="";
        while(getline(textfile,str)){
            inputtext+=str;
            inputtext.push_back('\n');
        }
        cout << inputtext << endl;    }
    else{
        cout << "File never opened :(" << endl;
    }
    
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
