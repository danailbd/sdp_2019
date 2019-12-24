#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include "../lib/testing-framework.h"


#define MISSING_INTERPOLATION_VAR -1

const std::string LESS_VARIABLES_ERROR = "Interpolation variable missing!";
const std::string MORE_VARIABLES_ERROR = "Additional interpolation variables!";

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
        } else if (c == ')' && operands.size() > 1) {
            int a = operands.top(); operands.pop();
            int b = operands.top(); operands.pop();
            char op = operators.top(); operators.pop();
            
            operands.push(evalSimpleExpression(a, b, op));
        }
    }

    return operands.top();
}

int getNextVarableIndex(std::string& expression, int startIdx)
{
    for (int i = startIdx; i < (int)expression.length(); ++i) {
        if (expression[i] == '{') {
            return i;
        }
    }

    return -1;
}

std::string getSubstring(std::string str, int startIdx, int endIdx)
{
    std::string result = "";

    for (int i = startIdx; i < endIdx; ++i) {
        result += str[i];
    }

    return result;
}

std::string interpolate(std::string& expression, std::vector<int>& values, std::string& error)
{
    std::string interpolatedExpr = "";
    int previousVarIdx = 0,
        variableIdx = 0;

    // while next var
    for (auto value : values) {
        variableIdx = getNextVarableIndex(expression, previousVarIdx);

        if (variableIdx == MISSING_INTERPOLATION_VAR) {
            error = MORE_VARIABLES_ERROR;
            return "";
        }
        
        // now omit the variable, replacing it with value
        interpolatedExpr += getSubstring(expression, previousVarIdx, variableIdx) + std::to_string(value);

        // skip the {}
        previousVarIdx = variableIdx + 2;
    }

    // simply copy the remaining symbols
    interpolatedExpr += getSubstring(expression, previousVarIdx, expression.length());


    if (getNextVarableIndex(expression, previousVarIdx) != MISSING_INTERPOLATION_VAR) {
        error = LESS_VARIABLES_ERROR;
        return "";
    }

    return interpolatedExpr;
}

class Error
{
public:
    Error (std::string msg) : m_msg(msg)
    {}

    virtual ~Error () {};

    std::string getMessage() const {
        return m_msg;
    }

private:
    std::string m_msg;
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

    std::string singleOperand = "(1)";
    res = evaluate(singleOperand);

    std::cout << res << (res == 1 ? "true" : "false");
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

void test_interpolation()
{
    std::string simpleIterpolation = "(1 + ({} + {}))";
    std::vector<int> values = {1, 2};
    std::string error = "";


    std::string interpolatedExpr = interpolate(simpleIterpolation, values, error);

    UnitTests::AssertEq<std::string>( "", error, "There isn't an error" );
    UnitTests::AssertEq<std::string>( "(1 + (1 + 2))", interpolatedExpr, "Correct expression is returned" );

    std::string moreVarIntepolation = "(1 + ({} + 1))";
    values = {1, 2};

    interpolatedExpr = interpolate(moreVarIntepolation, values, error);

    UnitTests::AssertEq<std::string>( MORE_VARIABLES_ERROR, error, "There is an error" );
    UnitTests::AssertEq<std::string>( "", interpolatedExpr, "Correct expression is returned" );


    std::string lessVarIntepolation = "(1 + ({} + {}))";
    values = {1};

    interpolatedExpr = interpolate(lessVarIntepolation, values, error);

    UnitTests::AssertEq<std::string>( LESS_VARIABLES_ERROR, error, "There is an error" );
    UnitTests::AssertEq<std::string>( "", interpolatedExpr, "Correct expression is returned" );
}

int main()
{
    //test_validate(); 
    //test_eval(); 
    test_interpolation();

    return 0;
}
