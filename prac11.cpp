#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cctype>
#include <map>

using namespace std;

// Structure to represent a quadruple
struct Quadruple {
    string op;
    string arg1;
    string arg2;
    string result;
};

// Function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to get the precedence of an operator
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to convert infix expression to postfix (RPN)
string infixToPostfix(const string& expression) {
    stack<char> operators;
    string postfix;
    for (char ch : expression) {
        if (isspace(ch)) continue;
        if (isdigit(ch) || ch == '.') {
            postfix += ch;
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += ' ';
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Remove '(' from stack
        } else if (isOperator(ch)) {
            postfix += ' ';
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            operators.push(ch);
        }
    }
    while (!operators.empty()) {
        postfix += ' ';
        postfix += operators.top();
        operators.pop();
    }
    return postfix;
}

// Function to generate quadruples from postfix expression
vector<Quadruple> generateQuadruples(const string& postfix) {
    stack<string> operands;
    vector<Quadruple> quadruples;
    int tempCount = 0;

    string token;
    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];
        if (isdigit(ch) || ch == '.') {
            token += ch;
        } else if (isspace(ch)) {
            if (!token.empty()) {
                operands.push(token);
                token.clear();
            }
        } else if (isOperator(ch)) {
            string op2 = operands.top(); operands.pop();
            string op1 = operands.top(); operands.pop();
            string temp = "t" + to_string(++tempCount);
            quadruples.push_back({string(1, ch), op1, op2, temp});
            operands.push(temp);
        }
    }
    return quadruples;
}

// Function to print the quadruple table
void printQuadruples(const vector<Quadruple>& quadruples) {
    cout << "Operator | Operand 1 | Operand 2 | Result" << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& quad : quadruples) {
        cout << quad.op << "       | " << quad.arg1 << "       | " << quad.arg2 << "       | " << quad.result << endl;
    }
}

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    // Convert infix to postfix
    string postfix = infixToPostfix(expression);
    cout << "Postfix expression: " << postfix << endl;

    // Generate quadruples
    vector<Quadruple> quadruples = generateQuadruples(postfix);

    // Print quadruple table
    printQuadruples(quadruples);

    return 0;
}