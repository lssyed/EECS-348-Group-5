# ============================================================
# Arithmetic Expression Evaluator (Reference Implementation)
# ============================================================
# This program evaluates expressions such as:
# 2 + 3 * 4
# (2 + 3) * 4
# 2 ** 3 ** 2
#
# The parser follows this precedence hierarchy:
#
# Expression → + -
# Term       → * / %
# Power      → **
# Unary      → + -
# Primary    → numbers and parentheses
#
# Each grammar rule corresponds to ONE function.
# ============================================================


class Parser:

    # --------------------------------------------------------
    # Constructor
    # --------------------------------------------------------
    # Runs once when the parser is created.
    # Stores the input expression and initializes the index
    # that moves through the string during parsing.
    # --------------------------------------------------------
    def __init__(self, text):
        self.text = text
        self.pos = 0
        self.current_char = text[self.pos] if text else None


    # --------------------------------------------------------
    # Move to the next character in the input
    # --------------------------------------------------------
    # Called whenever we "consume" a character.
    # This moves the parser forward.
    # --------------------------------------------------------
    def advance(self):
        self.pos += 1

        if self.pos < len(self.text):
            self.current_char = self.text[self.pos]
        else:
            self.current_char = None


    # --------------------------------------------------------
    # Skip whitespace
    # --------------------------------------------------------
    # Called whenever spaces appear in the expression.
    # Example: "2 + 3"
    # --------------------------------------------------------
    def skip_whitespace(self):
        while self.current_char is not None and self.current_char.isspace():
            self.advance()


    # --------------------------------------------------------
    # Parse numbers
    # --------------------------------------------------------
    # Called when the parser detects a digit.
    # Reads all digits and converts them into an integer.
    #
    # Example input:
    # "123"
    #
    # Returns:
    # 123
    # --------------------------------------------------------
    def number(self):

        result = ""

        while self.current_char is not None and self.current_char.isdigit():
            result += self.current_char
            self.advance()

        return int(result)


    # ========================================================
    # PRIMARY PARSER
    # ========================================================
    # Handles:
    #   numbers
    #   parentheses
    #
    # Grammar rule:
    # Primary → NUMBER | '(' Expression ')'
    #
    # This is the LOWEST level of the parser.
    # Every higher level eventually calls this function.
    # ========================================================
    def parse_primary(self):

        self.skip_whitespace()

        # Case 1: Number
        if self.current_char is not None and self.current_char.isdigit():
            return self.number()

        # Case 2: Parentheses
        if self.current_char == '(':

            # consume '('
            self.advance()

            # parse the inside expression
            result = self.parse_expression()

            self.skip_whitespace()

            # consume ')'
            if self.current_char == ')':
                self.advance()
            else:
                raise Exception("Missing closing parenthesis")

            return result

        raise Exception("Invalid expression")


    # ========================================================
    # UNARY PARSER
    # ========================================================
    # Handles unary operators:
    #   +5
    #   -5
    #
    # Grammar rule:
    # Unary → (+ | -) Unary | Primary
    #
    # Example:
    # -3  → returns -3
    # +5  → returns 5
    # ========================================================
    def parse_unary(self):

        self.skip_whitespace()

        if self.current_char == '+':
            self.advance()
            return +self.parse_unary()

        if self.current_char == '-':
            self.advance()
            return -self.parse_unary()

        return self.parse_primary()


    # ========================================================
    # POWER PARSER
    # ========================================================
    # Handles exponentiation:
    #   **
    #
    # Grammar rule:
    # Power → Unary (** Power)?
    #
    # Important:
    # exponentiation is RIGHT ASSOCIATIVE
    #
    # Example:
    # 2 ** 3 ** 2
    #
    # becomes
    # 2 ** (3 ** 2)
    # ========================================================
    def parse_power(self):

        left = self.parse_unary()

        self.skip_whitespace()

        if self.current_char == '*':

            # check if it is **
            saved_pos = self.pos
            self.advance()

            if self.current_char == '*':
                self.advance()

                right = self.parse_power()

                return left ** right
            else:
                # not actually **
                self.pos = saved_pos
                self.current_char = '*'

        return left


    # ========================================================
    # TERM PARSER
    # ========================================================
    # Handles:
    #   *
    #   /
    #   %
    #
    # Grammar rule:
    # Term → Power ((*, /, %) Power)*
    #
    # Example:
    # 3 * 4 / 2
    # ========================================================
    def parse_term(self):

        result = self.parse_power()

        while True:

            self.skip_whitespace()

            if self.current_char == '*':
                self.advance()
                result *= self.parse_power()

            elif self.current_char == '/':
                self.advance()
                result /= self.parse_power()

            elif self.current_char == '%':
                self.advance()
                result %= self.parse_power()

            else:
                break

        return result


    # ========================================================
    # EXPRESSION PARSER
    # ========================================================
    # Handles:
    #   +
    #   -
    #
    # Grammar rule:
    # Expression → Term ((+ | -) Term)*
    #
    # This is the TOP LEVEL parser.
    # The entire program starts here.
    # ========================================================
    def parse_expression(self):

        result = self.parse_term()

        while True:

            self.skip_whitespace()

            if self.current_char == '+':
                self.advance()
                result += self.parse_term()

            elif self.current_char == '-':
                self.advance()
                result -= self.parse_term()

            else:
                break

        return result


# ============================================================
# MAIN PROGRAM ENTRY
# ============================================================
# This is where the parser is started.
# ------------------------------------------------------------
# 1. User enters expression
# 2. Parser object created
# 3. parse_expression() is called
# 4. Final result printed
# ============================================================

def evaluate(expression):

    parser = Parser(expression)

    return parser.parse_expression()


# ------------------------------------------------------------
# Example usage
# ------------------------------------------------------------

expr = input("Enter expression: ")

result = evaluate(expr)

print("Result:", result)