/* This file contains the parsers for handling expressions*/
 #include <iostream>
 #include <string>
 #include <cmath>



 class Parser {
    private:
        std::string text;
        int n; //Length of string
        int position; //Position
        char curr_char;

    public:

        Parser(std::string input){
            text = input;
            position = 0;
            curr_char = text[position];
            n = text.length();
        }

        //Moving to next character in input
        void advance(){
            position += 1;

            if (position < n){
                curr_char = text[position];
            } else {
                curr_char = 0;
            }
        }

        //Skipping whitespace
        void skip_whitespace(){
            while (curr_char != 0 && std::isspace(curr_char)){
                advance();
            }
        }

        //Parsing numbers
        int number(){
            std::string result;
            int number;

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


        //Power Parser
        int parse_power(){
            int left; 
            int right;
            int temp_position;

            left = parse_unary();

            skip_whitespace();

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
                    result /= parse_power();
                } else if (curr_char == '%'){
                    advance();
                    result %= parse_power();
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
 };


//gathers expressions to parse and creates object of it
int evaluate(const std::string& expression){
   Parser parser(expression);
   return parser.parse_expression(); 
}



int main() {
    std::string expr;
    std::cout<<"Enter your expression: ";
    std::cin>>expr;

    int result = evaluate(expr);
    std::cout<<"Result: "<<result;
    return 0;
}

