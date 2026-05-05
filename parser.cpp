/* This file contains the parsers for handling expressions*/
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept> // Added for std::runtime_error
#include <cctype> // Added for std::isspace and std::isdigit

class Parser {
    private:
        std::string text;
        int n; // Length of string
        int position; // Position as int
        char curr_char;

    public:
        Parser(std::string input){
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
        // Move to next character
        void advance(){
            position += 1;
            if (position < n){
                curr_char = text[position];
            } else {
                curr_char = 0;
            }
        }
        // Skip whitespace
        void skip_whitespace(){
            while (curr_char != 0 && std::isspace(curr_char)){
                advance();
            }
        }

        // Parse numbers (now supports decimals)
        double number(){
            std::string result;
            bool has_decimal = false;

            while (curr_char != 0 && (std::isdigit(curr_char) || curr_char == '.')){
                if (curr_char == '.'){
                    if (has_decimal){
                        throw std::runtime_error("Invalid number format");
                    }
                    has_decimal = true;
                }
                result += curr_char;
                advance();
            }

            return std::stod(result);
        }

        // Primary parser
        //Lowest level of the parser that includes parsing for parentheses
        double parse_primary(){
            double result;
            skip_whitespace();
            //Case 1: Number
            if (curr_char != 0 && (std::isdigit(curr_char) || curr_char == '.')){
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

        // Unary parser
        double parse_unary(){
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
                    return std::pow(left, right);
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
                        throw std::runtime_error("Division by zero");
                    }
                    result /= right_side;

                } else if (curr_char == '%'){
                    advance();
                    double right_side = parse_power();
                    if (right_side == 0){
                        throw std::runtime_error("Modulo by zero");
                    }
                    result = std::fmod(result, right_side);

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
                throw std::runtime_error("Invalid expression: unexpected characters at the end.");
            }

            return result;
        }
};

//gathers expressions to parse and creates object of it
double evaluate(const std::string& expression){
    Parser parser(expression);
    return parser.parse();
}

int main() {
    std::string expr;
    std::cout << "Enter your expression: ";
    // Using std::cin >> expr would stop reading at the first whitespace.
    std::getline(std::cin, expr);
    //Wraps the execution in a try-catch block for robust error handling
    try {
        double result = evaluate(expr);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}