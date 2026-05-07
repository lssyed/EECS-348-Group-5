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
            // Move to the next character in the input string and update the current character.

            position += 1;

            if (position < n) {
                // If we have not reached the end of the input string, we update curr_char to the next character in the string.

                curr_char = text[position];
            }
            else {
                // If we have reached the end of the input string, we set curr_char to 0 (null character) to indicate that there are no more characters to process.

                curr_char = 0;
            }
        }

        
        void skip_whitespace(){
            // Skip whitespace
            
            while (curr_char != 0 && isspace(curr_char)) {
                // If the current character is a whitespace, we call advance() to move to the next character.

                advance();
            }
        }


        double number(){
            // Parse numbers (now supports decimals)
    
            string result;
            bool has_decimal = false;

            while (curr_char != 0 && (isdigit(curr_char) || curr_char == '.')) {
                // If the current character is a digit or a decimal point, we append it to the result string. We also check for multiple decimal points, which would indicate an invalid number format.

                if (curr_char == '.') {
                    // If we encounter a decimal point, we check if we have already seen one. If we have, then the number format is invalid (e.g., "3.14.15").

                    if (has_decimal) {
                        // If we have already seen a decimal point, we throw a runtime error indicating an invalid number format.

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
                return +parse_unary(); //Plus changes nothing, just recurse
            }
            
            if (curr_char == '-'){
            
                advance();
                return -parse_unary(); // Applies the unary minus (negation) to the following term
            }
            
            return parse_power(); //Executes the next level of parsing (power) if there are no unary operators.
        }

        // Power parser (**)
        double parse_power(){ //Declares a function to parse exponentiation expressions.
            double left = parse_primary(); // Parses the left-hand side of the exponentiation expression, which can be a number or a parenthesized expression.
            skip_whitespace(); // Skips any whitespace characters

            if (curr_char == '*'){ // Checks if the current character is an asterisk, which indicates the start of an exponentiation operator (**).
                //check for repeating
                int temp_position = position;
                advance();
                if (curr_char == '*'){ // If the next character is also an asterisk, we have a valid exponentiation operator. 
                //We then advance again to move past the second asterisk and parse the right-hand side of the exponentiation expression using parse_unary().
                    advance();
                    double right = parse_unary();
                    return pow(left, right);
                } else {
                    position = temp_position;
                    curr_char = '*'; 
                }
            }

            return left; // Returns the left-hand side if there is no exponentiation operator, allowing the parser to move on to multication, division, and modulo operations.
        }

        // Term parser (*, /, %)
        double parse_term(){ // This function is responsible for parsing multiplication, division, and modulo operations, which have higher precedence than addition and subtraction.
            double result = parse_unary(); 
            while (true){ //Enters a loop to handle multiple multiplication, division, or modulo operations in sequence.
                skip_whitespace(); 

                if (curr_char == '*'){ // If the current character is an asterisk, we advance to the next character and parse the right-hand side of the multiplication expression using parse_unary(). We then multiply the current result by the parsed value.
                    advance();
                    result *= parse_unary();

                } else if (curr_char == '/'){ // If the current character is a forward slash, we advance to the next character and parse the right-hand side of the division expression using parse_unary(). We also check for division by zero, which would throw a runtime error. 
                    // If the division is valid, we divide the current result by the parsed value.
                    advance();
                    double right_side = parse_unary(); // Parses the right-hand side of the division expression.
                    if (right_side == 0){ // Checks for division by zero. If the parsed value is zero, we throw a runtime error indicating that division by zero is not allowed.
                        throw runtime_error("Division by zero");
                    }
                    result /= right_side; // If the division is valid, we divide the current result by the parsed value.

                } else if (curr_char == '%'){ // Parses the next term using parse_unary() to perform modulo.
                    advance();
                    double right_side = parse_unary();
                    if (right_side == 0){
                        throw runtime_error("Modulo by zero");
                    }
                    result = fmod(result, right_side); // Computes the modulo (remainder) using fmod() and updates the result.
                } else {
                    break;
                }
            }

            return result; // Returns the final result of the parsed term after processing all multiplication, division, and modulo operations.
        }

        // Expression parser (+, -)
        double parse_expression(){ // Declares a function to parse addition and subtraction operations.
            double result = parse_term(); //

            while (true){ // Enters a loop to handle multiple addition or subtraction operations.
                skip_whitespace();

                if (curr_char == '+'){ // If the current character is a plus sign, we advance to the next character and parse the right-hand side of the addition expression using parse_term().
                    advance();
                    result += parse_term();

                } else if (curr_char == '-'){ // If the current character is a minus sign, we advance to the next character and parse the right-hand side of the subtraction expression using parse_term().
                    advance();
                    result -= parse_term();

                } else {
                    break; // If there are no more addition or subtraction operators, we break out of the loop and return the final result.
                }
            }

            return result; // Returns the final result of the parsed expression after processing all addition and subtraction operations.
        }

        // Ensure full parsing
        double parse(){ //Declares a function to ensure that the entire input string is parsed and that there are no unexpected characters left after parsing a valid expression.
            double result = parse_expression();
            skip_whitespace();
            
            // If there are still characters left after parsing a valid expression
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

void run_tests() { //Testing functions to see if the parser is working correctly.
    cout << "Running Automated Test Suite" << endl;

    // Testing Valid Expressions
    string valid_tests[] = {
        "3+4",              // Addition
        "8-(5-2)",          // Subtraction with Parentheses
        "10*2/5",           // Multiplication and Division
        "2**3",             // Exponentiation
        "-(+1)+(+2)"        // Unary Operators
    };
    double expected_results[] = {7, 5, 4, 8, 1}; // Expected results for the valid case tests.

    for (int i = 0; i < 5; i++) { // Loop through the valid test cases, evaluate each expression, and compare the result to the expected value.
            double result = evaluate(valid_tests[i]);
            cout << "Test " << i+1 << " [" << valid_tests[i] << "]: ";
            if (abs(result - expected_results[i]) < 0.0001) { // Pass if the result is the same, Fail if the result is different.
                cout << "PASS" << endl;
            } else {
                cout << "FAIL (Expected " << expected_results[i] << ", got " << result << ")" << endl;
            }
        } catch (const exception& e) { //
            cout << "FAIL (Threw error: " << e.what() << ")" << endl;
        }
    }

    // Testing Invalid Expressions (Testing Error Handling)
    cout << "\n Testing Invalid Expressions (Errors are Expected)" << endl;
    string invalid_tests[] = {
        "2*(4+3-1",          // Unmatched Parentheses
        "4/0",               // Division by Zero
        "7 & 3"              // Invalid Characters
    };

    for (int i = 0; i < 3; i++) { // Loop through the invalid test cases, evaluate each expression, and check if an exception is thrown.
        try {
            double result = evaluate(invalid_tests[i]);
            cout << "Invalid Test " << i+1 << " [" << invalid_tests[i] << "]: FAIL (Didn't catch the error)" << endl;
        } catch (const exception& e) {
            cout << "Invalid Test " << i+1 << " [" << invalid_tests[i] << "]: PASS (Caught: " << e.what() << ")" << endl;
        }
    }
    cout << "\n" << endl;
}

int main() { // Main function to run the parser, test cases and handle user input.
    string choice;
    cout << "Would you like to run built-in tests? (Y/N): "; // Asks user if they want to run the built-in tests cases.
    getline(cin, choice);

    if (choice == "y" || choice == "Y") { // If the user types "Y" or "y", we call the run_tests() function to execute the predefined test cases.
        run_tests();
    }

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

    return 0; // Returns 0 to indicate that the program ended successfully.
}
