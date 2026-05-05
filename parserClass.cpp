#include <iostream>
#include <cctype>
#include <string>
#include <cmath>
using namespace std;


class Parser{

    public:
        Parser(string str); // Constructor to initialize the parser with the input string
        bool isSpace(char c); // Helper function to check if a character is a whitespace character
        void skipWhiteSpace(); // Helper function to skip over any whitespace characters in the input string
        void advance(); // Helper function to move the current position in the input string forward by one character
        int number(); // Helper function to parse a number from the input string and return its integer value
        int primaryParser(); // Helper function to parse a primary expression (number or parenthesized expression) from the input string and return its integer value
        int parseUnary(); // Helper function to parse a unary expression (positive or negative) from the input string and return its integer value
        int parsePower(); // Helper function to parse a power expression (exponentiation) from the input string and return its integer value
        int parseTerm(); // Helper function to parse a term (multiplication, division, or modulus) from the input string and return its integer value
        int parseExpression(); // Helper function to parse an expression (addition or subtraction) from the input string and return its integer value
        


    private:
        string text = NULL; // The input string to be parsed
        int pos = 0; // The current position in the input string
        char currChar = text[pos]; // The current character being processed in the input string
};

Parser::Parser(string str){
    // Constructor to initialize the parser with the input string
    text = str;
}

void Parser::advance(){
    // Move to the next character in the input string
    pos +=1;
    if(pos < text.length()){
        currChar = text[pos];
    }
    else{
        currChar = NULL;
    }

}
bool Parser::isSpace(char c){
    // Check if the character is a whitespace character (space, tab, newline, etc.)
    if(c == ' '){
        return true;
    }
    else{
        return false;
    }

}
void Parser::skipWhiteSpace(){
    // Skip over any whitespace characters in the input string
    while(currChar != NULL && isSpace(currChar)){
        advance();
    }
}

int Parser::number(){
    // Parse a number from the input string and return its integer value
    string result = "";
    
    while( currChar!= NULL && isdigit(currChar) ){
        result += currChar;
        advance();
    }
    //stoi is string to integer
    return stoi(result);
}

int Parser::primaryParser(){
    // Parse a primary expression (number or parenthesized expression) from the input string and return its integer value
    int result;
    // Skip any leading whitespace characters before parsing the primary expression
    skipWhiteSpace();

    if(currChar!= NULL && isdigit(currChar)){
        // Case 1: Number
        return number();
    }

    if (currChar == '('){
        // Case 2: Parenthesis
        advance();
        // result = parseExpression();
        skipWhiteSpace();
        // After parsing the expression inside the parentheses, check for a closing parenthesis
        if(currChar == ')'){
            advance();
        }
        else{
            cout << "MISSING CLOSING PARENTHESIS: " << endl;
            return;
        }
        return result;
    }
    cout << "INVALID EXPRESSION: " << endl;
    

}

int Parser::parseUnary(){
    // Parse a unary expression (positive or negative) from the input string and return its integer value
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
    // Parse a power expression (exponentiation) from the input string and return its integer value
    int left = parseUnary();
    skipWhiteSpace();

    if (currChar == '*'){
        char savedPos = pos;
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
    // Parse a term (multiplication, division, or modulus) from the input string and return its integer value
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
    // Parse an expression (addition or subtraction) from the input string and return its integer value
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
    // Gather expressions to parse and create an object of the Parser class
    Parser parser(expression);

    return parser.parseExpression();
}