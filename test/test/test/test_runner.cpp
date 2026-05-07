/*
 * Test Runner for Arithmetic Expression Evaluator
 * Verifies implementation against project requirements
 */

#include <iostream>
#include <string>
#include "../src/parserClass.h" // Include the interface 

void runTest(std::string identifier, std::string input, double expected) {
    Parser myParser;
    try {
        double result = myParser.evaluate(input);
        if (result == expected) {
            std::cout << "[PASS] " << identifier << ": " << input << " = " << result << std::endl;
        } else {
            std::cout << "[FAIL] " << identifier << ": Expected " << expected << " but got " << result << std::endl;
        }
    } catch (...) {
        std::cout << "[ERROR] " << identifier << ": An exception occurred during evaluation." << std::endl;
    }
}

int main() {
    std::cout << "--- Starting Unit Tests ---" << std::endl;

    // TC-VAL-01: Basic Addition [cite: 69]
    runTest("TC-VAL-01", "3 + 4", 7.0);

    // TC-VAL-04: Exponentiation [cite: 79]
    runTest("TC-VAL-04", "2 ** 3", 8.0);

    return 0;
}