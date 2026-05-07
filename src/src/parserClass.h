#ifndef PARSER_CLASS_H
#define PARSER_CLASS_H

#include <string>

class Parser {
public:
    // This matches the objective to parse and evaluate
    double evaluate(std::string expression); 
};

#endif