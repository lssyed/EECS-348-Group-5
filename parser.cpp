/* This file contains the parsers for handling expressions*/
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept> // Added for std::runtime_error
#include <cctype> // Added for std::isspace and std::isdigit

class Parser {
    private:
        std::string text; // Input string
        int n; // Length of string
        int position; // Position
        char curr_char;
    public:
        Parser(std::string input){
            // Initialize the parser with the input string
            text = input;
            position = 0;
            n = text.length();
            // Prevent out-of-bounds on empty input
            if (n > 0) {
                curr_char = text[position];
            } else {
                curr_char = 0;
            }
        }
        //Moving to next character in input
        void advance(){
            // Move to the next character and update curr_char
            position += 1;
            if (position < n){
                curr_char = text[position];
            } else {
                curr_char = 0;
            }
        }
        //Skipping whitespace
        void skip_whitespace(){
            // Skip any whitespace characters
            while (curr_char != 0 && std::isspace(curr_char)){
                advance();
            }
        }
        //Parsing numbers
        int number(){
            // Parse a sequence of digits into an integer
            std::string result; // String to accumulate the digits of the number
            int number; // Variable to store the final number
            while (curr_char != 0 && std::isdigit(curr_char)){
                result += curr_char;
                advance();
            }
            number = std::stoi(result);
            return number;
        }
        //Primary Parser
        //Lowest level of the parser that includes parsing for parentheses
        int parse_primary(){
            // Parse a primary expression, which can be a number or an expression in parentheses
            int result;
            skip_whitespace();
            //Case 1: Number
            if (curr_char != 0 && std::isdigit(curr_char)){
                return number();
            }
            //Case 2: Parenthesis
            if (curr_char == '('){
                advance(); 
                //parse inside expression
                result = parse_expression();
                skip_whitespace();
                if (curr_char == ')'){
                    advance();
                } else {
                    throw std::runtime_error("Missing closing parenthesis");
                }
                return result;
            }
            throw std::runtime_error("Invalid expression");
        }
        //Unary Parser
        int parse_unary(){
            // Handle unary plus and minus operators
            skip_whitespace();
            if (curr_char == '+'){
                // Unary plus doesn't change the value, but we still need to advance and parse the next part
                advance();
                return +parse_unary();
            }
            if (curr_char == '-'){
                // Unary minus negates the value, so we advance and parse the next part, then negate it
                advance();
                return -parse_unary();
            }
            return parse_primary(); // If it's not a unary operator, parse it as a primary expression
        }

        //Power Parser
        int parse_power(){
            // Handle exponentiation, which is right-associative (e.g., 2 ** 3 ** 2 is 2 ** (3 ** 2))
            int left; // Store the left-hand side of the exponentiation
            int right; // Store the right-hand side of the exponentiation
            int temp_position; // Temporary variable to store the position before checking for '**'
            left = parse_unary(); // Parse the left-hand side first
            skip_whitespace(); // Check for the '**' operator
            if (curr_char == '*'){
                //Check for repeat
                temp_position = position;
                advance();
                if (curr_char == '*'){
                    advance();
                    right = parse_power();
                    return (int)std::pow(left, right);
                } else {
                    position = temp_position;
                    curr_char = '*';
                }
            }
            return left;
        }

        //Term parser
        int parse_term(){
            int result;
            result = parse_power();
            while (true){
                skip_whitespace();
                if (curr_char == '*'){
                    advance();
                    result *= parse_power();
                } else if (curr_char == '/'){
                    advance();
                    // Added check for division by zero
                    int right_side = parse_power();
                    if (right_side == 0) {
                        throw std::runtime_error("Division by zero");
                    }
                    result /= right_side;
                } else if (curr_char == '%'){
                    advance();
                    // Added check for modulo by zero
                    int right_side = parse_power();
                    if (right_side == 0) {
                        throw std::runtime_error("Modulo by zero");
                    }
                    result %= right_side;
                } else {
                    break;
                }
            }
            return result;
        }
        //Expression parser
        int parse_expression(){
            int result;
            result = parse_term();
            while (true){
                skip_whitespace();
                if (curr_char == '+'){
                    advance();
                    result += parse_term();
                } else if (curr_char == '-') {
                    advance();
                    result -= parse_term();
                } else {
                    break;
                }
            }
            return result;
        }
        // Ensures entire string is evaluated
        int parse() {
            int result = parse_expression();
            skip_whitespace();
            
            // If there are still characters left after parsing a valid expression (e.g., "3 + 4 )")
            // then the overall expression is invalid.
            if (curr_char != 0) {
                throw std::runtime_error("Invalid expression: unexpected characters at the end.");
            }
            
            return result;
        }
};

//gathers expressions to parse and creates object of it
int evaluate(const std::string& expression){
Parser parser(expression);
return parser.parse(); 
}

int main() {
std::string expr;
std::cout<<"Enter your expression: ";
// Using std::cin >> expr would stop reading at the first whitespace.
std::getline(std::cin, expr);
//Wraps the execution in a try-catch block for robust error handling
try {
    int result = evaluate(expr);
    std::cout << "Result: " << result << std::endl;
} catch (const std::exception& e) {
    // This will neatly print "Division by zero" or "Invalid expression" without crashing the app
    std::cerr << "Error: " << e.what() << std::endl; 
}
return 0;
}