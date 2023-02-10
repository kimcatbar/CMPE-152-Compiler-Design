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
/*enum class TokenType {
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
    EOF
};*/

class Scanner {
    public:
    Scanner() {
        /* set up possible input word as key, and tokentype as value */
        
    }
    Scanner(string input){
        keyword = {{"and", "AND"}, {"array", "ARRAY"}, {"asm", "ASM"}, {"begin", "BEGIN"}, {"break", "BREAK"}, {"case", "CASE"}, {"const", "CONST"}, {"constructor", "CONSTRUCTOR"}, {"continue", "CONTINUE"}, {"destructor", "DESTRUCTOR"}, {"div", "DIV"}, {"do", "DO"}, {"downto", "DOWNTO"}, {"else", "ELSE"}, {"end", "END"}, {"false", "FALSE"}, {"file", "FILE"}, {"for", "FOR"}, {"function", "FUNCTION"}, {"goto", "GOTO"}, {"if", "IF"}, {"implementation", "IMPLEMENTATION"}, {"in", "IN"}, {"inline", "INLINE"}, {"interface", "INTERFACE"}, {"label", "LABEL"}, {"mod", "MOD"}, {"nil", "NIL"}, {"not", "NOT"}, {"object", "OBJECT"}, {"of", "OF"}, {"on", "ON"}, {"operator", "OPERATOR"}, {"or", "OR"}, {"packed", "PACKED"}, {"procedure", "PROCEDURE"}, {"program", "PROGRAM"}, {"record", "RECORD"}, {"repeat", "REPEAT"}, {"set", "SET"}, {"shl", "SHL"}, {"SHR", "SHR"}, {"string", "STRING"}, {"then", "THEN"}, {"to", "TO"}, {"true", "TRUE"}, {"type", "TYPE"}, {"unit", "UNIT"}, {"until", "UNTIL"}, {"uses", "USES"}, {"var", "VAR"}, {"while", "WHILE"}, {"with", "WITH"}, {"xor", "XOR"}, {"(integer)", "INTEGER"}, {"(real number)", "REAL"}, {"(identifier)", "INDENTIFIER"}, {"+", "PLUSOP"}, {"-", "MINUSOP"}, {"*", "MULTOP"}, {"/", "DIVOP"}, {":=", "ASSIGN"}, {"=", "EQUAL"}, {"<>", "NE"}, {"<=", "LTEQ"}, {">=", "GTEQ"}, {"<", "LT"}, {">", "GT"}, {"+=", "PLUSEQUAL"}, {"-=", "MINUSEQUAL"}, {"*=", "MULTEQUAL"}, {"/=", "DIVEQUAL"}, {"^", "CARAT"}, {";", "SEMICOLON"}, {",", "COMMA"}, {"(", "LPAREN"}, {")", "RPAREN"}, {"[", "LBRACKET"}, {"]", "RBRACKET"}, {"{", "LBRACE"}, {"}", "RBRACE"}, {"(*", "LCOMMENT"}, {"*)", "RCOMMENT"},{":","COLON"}};
        processdata(input);
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
                    in_stream.push_back(keyword[currentSymbol] + ": " + currentSymbol);
                    currentSymbol="";
                }
                currentWord.push_back(in);//add char to token variable
                currentState = 1;//tells is what previous char is
            }
            else if(((in >= '0') && (in <= '9')) || (in == '.') ){//if char is a number
                if(currentState == 3){
                    in_stream.push_back(keyword[currentSymbol] + ": " + currentSymbol);
                    currentSymbol = "";
                }
                if(currentWord.empty()){
                    currentNumber.push_back(in);
                }
                else{
                    currentWord.push_back(in);
                }
                currentState = 2;
            }
            else if((in  == '+') || (in == '-') || (in == '*') || (in == '/') || (in == ':') || (in == '=') || (in == '<') || (in == '>') || (in =='^') || (in == ';') || (in == ',') || (in == '(')
                    || (in == ')') || (in == '[') || (in == ']') || (in == '{') || (in == '}')){//if char is special symbol
                if(currentState == 0) {//if program is beginnining (state = 0)
                    currentSymbol.push_back(in);
                }
                else if(!currentWord.empty()){//if state 1
                    if(keyword.find(currentWord) != keyword.end()) {//detect if the key exists in map
                        in_stream.push_back(keyword[currentWord] + ": " + currentWord);//if it exists, store it in vector
                    }
                    else {
                        in_stream.push_back("INDENTIFIER: " + currentWord);//not a reserved word, it is identifier
                    }
                    currentSymbol.push_back(in);
                    currentWord = "";//set to empty since we've come accross a symbol token
                }
                else if(currentState == 2) {//previous state is a number
                    if(currentNumber.find('.') != std::string::npos){//if current number has a decimal point
                        in_stream.push_back("REAL: " + currentNumber);
                    }
                    else{
                        in_stream.push_back("INTEGER: " + currentNumber);
                    }
                    currentSymbol.push_back(in);
                    currentNumber = "";
                }
                else if(currentState == 3){//if prev char is a symbol -> (* or >=
                    string hypo = currentSymbol;
                    hypo.push_back(in);
                    if(keyword.count(hypo) == 0) {
                        in_stream.push_back(keyword[currentSymbol] + ": " + currentSymbol);
                        currentSymbol = "";
                        currentSymbol.push_back(in);
                    }
                    else {
                        in_stream.push_back(keyword[hypo] + ": " + hypo);
                        currentSymbol = "";
                    }
                }
                else if(currentState == 4) {
                    currentSymbol.push_back(in);
                }
                currentState = 3;
                
            }
            else if((in == ' ') || (in == '\n') || (in == '\t')){//if spaces detected
                if(!currentWord.empty()){//if current word NOT empty & cover state 1
                    in_stream.push_back(keyword[currentWord] + ": " + currentWord);
                    currentWord = "";//reset current word to be empty
                }
                else if(!currentNumber.empty()){//decide whether it is integer or real
                    if(currentNumber.find('.') != std::string::npos){//if current number has a decimal point
                        in_stream.push_back("REAL: " + currentNumber);
                    }
                    else{
                        in_stream.push_back("INTEGER: " + currentNumber);
                    }
                    currentNumber = "";
                }
                else if(!currentSymbol.empty()){
                    in_stream.push_back(keyword[currentSymbol] + ": " + currentSymbol);
                    currentSymbol = "";
                }
                currentState = 4;
            }
            else {
                cout << "Unrecgonized state/token/symbol.  " << in << endl;
            }
                
        }
        if(!currentWord.empty()){//if current word NOT empty & cover state 1
            in_stream.push_back(keyword[currentWord] + ": " + currentWord);
            currentWord = "";//reset current word to be empty
        }
        else if(!currentNumber.empty()){//decide whether it is integer or real
            if(currentNumber.find('.') != std::string::npos){//if current number has a decimal point
                in_stream.push_back("REAL: " + currentNumber);
            }
            else{
                in_stream.push_back("INTEGER: " + currentNumber);
            }
            currentNumber = "";
        }
        else if(!currentSymbol.empty()){
            in_stream.push_back(keyword[currentSymbol] + ": " + currentSymbol);
            currentSymbol = "";
        }
        //cout << "EOF" << endl;
    }
    string nexttoken() {//function to access next char in input file
        if(in_stream.size() > tokenIndex) {
            string token = in_stream[tokenIndex];
            tokenIndex++;
            return token;
        }
        return "EOF";
    }
    private:
    int tokenIndex = 0;
    map<string, string> keyword;
    vector<string> in_stream; //storing tokens after found from input stream
};

int main(int argc, const char * argv[]) {
    cout << argv[0] << endl;
    //feed text file
    ifstream textfile;
    ofstream outfile;
    //change to your own input file
    textfile.open("sampleinput1.txt");
    outfile.open("test-out.txt");
    if(outfile.is_open()){
        cout << "OF does exist." << endl;
    }
    if (textfile.is_open()){
        //cout << "File is open!" << endl;
        string inputtext ="";
        string str="";
        while(getline(textfile,str)){
            inputtext+=str;
            inputtext.push_back('\n');
        }
        Scanner scanner = Scanner(inputtext);
        string token = scanner.nexttoken();
        while(token != "EOF") {
            outfile << token << endl;
            token = scanner.nexttoken();
        }
         }
    else{
        cout << "File never opened :(" << endl;
    }
    textfile.close();
    outfile.close();
    
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
