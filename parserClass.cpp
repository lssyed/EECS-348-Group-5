#include <iostream>
#include <cctype>
#include <string>
#include <cmath>
using namespace std;


class Parser{

    public:
        Parser(string str);
        bool isSpace(char c);
        void skipWhiteSpace();
        void advance();
        int number();
        int primaryParser();
        int parseUnary();
        int parsePower();
        int parseTerm();
        int parseExpression();
        


    private:
        string text;
        int pos = 0;
        char currChar;
};

Parser::Parser(string str){
    text = str;
    pos = 0;
    currChar = (pos < text.length() ? text[pos] : '\0');
}

void Parser::advance(){
    pos +=1;
    if(pos < text.length()){
        currChar = text[pos];
    }
    else{
        currChar = '\0';
    }

}
bool Parser::isSpace(char c){
    if(c == ' '){
        return true;
    }
    else{
        return false;
    }

}
void Parser::skipWhiteSpace(){
    while(currChar != '\0' && isSpace(currChar)){
        advance();
    }
}

int Parser::number(){
    string result = "";
    
    while( currChar!= '\0' && isdigit(currChar) ){
        result += currChar;
        advance();
    }
    //stoi is string to integer
    return stoi(result);
}

int Parser::primaryParser(){
    int result;
    skipWhiteSpace();
    if(currChar!= '\0' && isdigit(currChar)){
        return number();
    }
    if (currChar == '('){
        advance();
        result = parseExpression();
        skipWhiteSpace();

        if(currChar == ')'){
            advance();
        }
        else{
            cout << "MISSING CLOSING PARENTHESIS: " << endl;
            return 0;
        }
        return result;
    }
    cout << "INVALID EXPRESSION" << endl;
    return 0;
}

int Parser::parseUnary(){
    skipWhiteSpace();

    if (currChar == '+'){
        advance();
        return +parseUnary();
    }

    if (currChar == '-'){
        advance();
        return -parseUnary();
    }
    return primaryParser();
}

int Parser::parsePower(){
    int left = parseUnary();
    skipWhiteSpace();

    if (currChar == '*'){
        int savedPos = pos;
        advance();

        if(currChar == '*'){
            advance();
            int right = parsePower();
            return pow(left, right);
        }
        else{
            pos = savedPos;
            currChar = '*';
        }
    }
    return left;
}

int Parser::parseTerm(){
    int result = parsePower();

    while(true){
        if (currChar == '*'){
            advance();
            result *= parsePower();
        }
        else if (currChar == '/'){
            advance();
            result /= parsePower();
        }
        else if (currChar == '%'){
            advance();
            result %= parsePower();
        }
        else{
            break;
        }

    }
    return result;

}



int Parser::parseExpression(){
    int result = parseTerm();

    while(true){
        skipWhiteSpace();

        if (currChar == '+'){
            advance();
            result += parseTerm();

        }
        else if (currChar == '-'){
            advance();
            result -= parseTerm();
        }
        else{
            break;
        }
    }
    return result;
}

int evaluate(string expression){
    Parser parser(expression);

    return parser.parseExpression();
}