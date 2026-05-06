/* This file contains the parsers for handling expressions*/
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept> // Added for std::runtime_error.
#include <cctype> // Added for std::isspace and std::isdigit.
using namespace std; // Using the standard namespace for convenience.

class Parser {
    private:

        string text; // Input string to parse
        int n; // Length of string
        int position; // Position as int
        char curr_char; // Current character as char

    public:

        Parser(string input){
            // Initialize the parser with the input string of the expression to be evaluated.

            text = input; // Store the input string
            position = 0; // variable to keep track of the current position in the input string
            n = text.length(); // Store the length of the input string

            if (n > 0) {
                curr_char = text[position];
            } else {
                curr_char = 0;
            }
        }
        
        void advance(){

            position += 1;

            if (position < n) {
                curr_char = text[position];
            }
            else {
                curr_char = 0;
            }
        }

        
        void skip_whitespace(){
            // Skip whitespace
            
            while (curr_char != 0 && isspace(curr_char)){
                advance();
            }
        }


        double number(){
            // Parse numbers (now supports decimals)
    
            string result;
            bool has_decimal = false;

            while (curr_char != 0 && (isdigit(curr_char) || curr_char == '.')){
                if (curr_char == '.'){
                    if (has_decimal){
                        throw runtime_error("Invalid number format");
                    }
                    has_decimal = true;
                }
                result += curr_char;
                advance();
            }

            return stod(result);
        }


        double parse_primary(){
            // Primary parser: numbers and parenthesis
            // This is the most basic level of parsing, handling numbers and parenthesized expressions.

            double result;
            skip_whitespace();

            //Case 1: Number
            if (curr_char != 0 && (isdigit(curr_char) || curr_char == '.')){
                return number();
            }
            
            //Case 2: Parenthesis
            if (curr_char == '('){
                
                // Move past the '(' and parse the expression inside
                advance();
                result = parse_expression();
                skip_whitespace();

                if (curr_char == ')'){
                    advance();
                }
                
                else {
                    throw runtime_error("Missing closing parenthesis");
                }
                
                return result;
            }

            // If we reach here, it means we have an invalid character for a primary expression.
            throw runtime_error("Invalid expression");
        }


        double parse_unary(){
            // Unary parser: handles unary plus and minus

            skip_whitespace();

            if (curr_char == '+'){
            
                advance();
                return +parse_unary();
            }
            
            if (curr_char == '-'){
            
                advance();
                return -parse_unary();
            }
            
            return parse_primary();
        }

        // Power parser (**)
        double parse_power(){
            double left = parse_unary();
            skip_whitespace();

            if (curr_char == '*'){
                //check for repeating
                int temp_position = position;
                advance();
                if (curr_char == '*'){
                    advance();
                    double right = parse_power();
                    return pow(left, right);
                } else {
                    position = temp_position;
                    curr_char = '*';
                }
            }

            return left;
        }

        // Term parser (*, /, %)
        double parse_term(){
            double result = parse_power();
            while (true){
                skip_whitespace();

                if (curr_char == '*'){
                    advance();
                    result *= parse_power();

                } else if (curr_char == '/'){
                    advance();
                    double right_side = parse_power();
                    if (right_side == 0){
                        throw runtime_error("Division by zero");
                    }
                    result /= right_side;

                } else if (curr_char == '%'){
                    advance();
                    double right_side = parse_power();
                    if (right_side == 0){
                        throw runtime_error("Modulo by zero");
                    }
                    result = fmod(result, right_side);

                } else {
                    break;
                }
            }

            return result;
        }

        // Expression parser (+, -)
        double parse_expression(){
            double result = parse_term();

            while (true){
                skip_whitespace();

                if (curr_char == '+'){
                    advance();
                    result += parse_term();

                } else if (curr_char == '-'){
                    advance();
                    result -= parse_term();

                } else {
                    break;
                }
            }

            return result;
        }

        // Ensure full parsing
        double parse(){
            double result = parse_expression();
            skip_whitespace();
            
            // If there are still characters left after parsing a valid expression (e.g., "3 + 4 )")
            // then the overall expression is invalid.
            if (curr_char != 0){
                throw runtime_error("Invalid expression: unexpected characters at the end.");
            }

            return result;
        }
};

//gathers expressions to parse and creates object of it
double evaluate(const string& expression){
    Parser parser(expression);
    return parser.parse();
}

int main() {
    string expr;
    cout << "Enter your expression: ";
    // Using cin >> expr would stop reading at the first whitespace.
    getline(cin, expr);
    //Wraps the execution in a try-catch block for robust error handling
    try {
        double result = evaluate(expr);
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}