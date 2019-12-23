#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include "../lib/testing-framework.h"

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isOperand(char c) {
    return c >= '0' && c <= '9';
}

int evalSimpleExpression(int a, int b, char op)
{
    switch(op) {
        case '+':
            return a + b;
        case '*':
            return a * b;
        case '-':
            return a - b;
        case '/':
            return a / b;
        default:
            return 0;
    }
}

int evaluate(std::string expression)
{
    std::stack<int>  operands;
    std::stack<char> operators;

    for (char c : expression) {
        if (c == ' ') continue;

        if (isOperand(c)) {
            operands.push(c - '0');
        } else if (isOperator(c)) {
            operators.push(c);
        } else if (c == ')') {
            int a = operands.top(); operands.pop();
            int b = operands.top(); operands.pop();
            char op = operators.top(); operators.pop();
            
            operands.push(evalSimpleExpression(a, b, op));


        }
    }

    return operands.top();
}

class Error
{
public:
    Error (std::string msg) : m_msg(msg)
    {}

    virtual ~Error () {};

    virtual std::string getMessage() const {
        return m_msg;
    }

private:
    size_t position;
};


/* bool validateBrackets() {} // Matching brackets */

/* bool validateOperations() { */
/* } */

bool validateOperands(char last) {
    return last == ')' || isOperand(last);
}

std::vector<std::string> validate(std::string expr) {
    std::vector<std::string> errors;

    int brackets = 0;

    bool hasOperand = false;

    for (int i = 0; i < (int)expr.size(); ++i) {
        
        if (expr[i] == '(') {
            brackets++;
        }
        else if (expr[i] == ')') {
            if (brackets == 0) errors.push_back("Brackets at pos: " + std::to_string(i+1));
            brackets--;
        }

        else if (isOperand(expr[i])) {
            if (hasOperand) 
                errors.push_back("Operation missing at pos: " + std::to_string(i-1));

            // continue for the next items
            hasOperand = true;
        }
        else if (isOperator(expr[i])) {
            if (!hasOperand)
                errors.push_back("Operand missing at pos: " + std::to_string(i-1));

            hasOperand = false;
        }
    }

    return errors;
}


void test_eval()
{
    std::string populatedExpression = "(1 + (2 * 3))";
    
    int res = evaluate(populatedExpression);

    std::cout << res << (res == 7 ? "true" : "false");
}


void test_validate()
{
    // ( + 1)
    // (1 1)
    // (1 (1))
    // (1)
    // (1+ (1))
    std::string moreBrackets = "(1 + (4 * 3)))";
    std::string lackOp = "(1  (6 * 3))";
    std::string lackOperand = "( + ({} * 3))";
    
    UnitTests::AssertEq( 1, (int)validate(moreBrackets).size() );
    UnitTests::AssertEq( std::string("Brackets at pos: 14"), validate(moreBrackets)[0] );

    UnitTests::AssertEq( 1, (int)validate(lackOp).size() );
    UnitTests::AssertEq( std::string("Operation missing at pos: 4"), validate(lackOp)[0] );
}


int main()
{
    /* test_validate(); */


    std::vector<int> v = {1, 2, 3};

    for (auto& number: v) {
        std::cout << number << std::endl;
    }

    return 0;
}
