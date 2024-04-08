#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <regex>

using namespace std;

// Data structures to store information about expressions and variables
struct Expression {
    int id;
    string code;
    bool isBusy;
};

struct Variable {
    string name;
    set<int> livePoints;
};

// Function to analyze the program and find available expressions and live variables
void analyzeProgram(const vector<string>& program) {
    vector<Expression> expressions;
    map<string, Variable> variables;

    // Regular expression patterns to match variable assignments and expressions
    regex varAssignPattern(R"(^\s*([\w_]+)\s*=\s*(.*)\s*;?$)");
    regex exprPattern(R"((?:\w+\s*[\+\-\*/]\s*)+\w+)");

    for (int i = 0; i < program.size(); i++) {
        string line = program[i];

        smatch match;
        if (regex_match(line, match, varAssignPattern)) {
            string varName = match[1];
            string exprCode = match[2];

            auto it = find_if(expressions.begin(), expressions.end(), [&](const Expression& expr) {
                return expr.code == exprCode;
            });

            if (it != expressions.end()) {
                expressions[it - expressions.begin()].isBusy = true;
            } else {
                expressions.push_back({ static_cast<int>(expressions.size()), exprCode, true });
            }

            variables[varName].name = varName;
            variables[varName].livePoints.insert(i);
        }

        // Find expressions in the line and add them to the expressions list
        string::const_iterator searchStart(line.cbegin());
        while (regex_search(searchStart, line.cend(), match, exprPattern)) {
            string exprCode = match.str();
            
            auto it = find_if(expressions.begin(), expressions.end(), [&](const Expression& expr) {
                return expr.code == exprCode;
            });

            if (it == expressions.end()) {
                expressions.push_back({ static_cast<int>(expressions.size()), exprCode, false });
            }

            searchStart = match.suffix().first;
        }

        // Find variable declarations and add them to the variables list
        regex varDeclPattern(R"(^\s*(?:int|double|float|char|bool)\s+([\w_]+)\s*(?:\s*\=\s*.+)?\s*;?$)");
        if (regex_match(line, match, varDeclPattern)) {
            string varName = match[1];
            variables[varName].name = varName;
            variables[varName].livePoints.insert(i);
        }
    }

    // Print the available expressions
    cout << "Available Expressions:" << endl;
    for (const Expression& expr : expressions) {
        if (!expr.isBusy) {
            cout << "Expression " << expr.id << ": " << expr.code << endl;
        }
    }

    // Print the live variables
    cout << "Live Variables:" << endl;
    for (const auto& pair : variables) {
        const Variable& var = pair.second;
        cout << "Variable " << var.name << ": ";
        for (int point : var.livePoints) {
            cout << point << " ";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./analyzer <input_file>" << endl;
        return 1;
    }

    const string inputFileName = argv[1];
    ifstream inputFile(inputFileName);

    if (!inputFile) {
        cout << "Failed to open input file: " << inputFileName << endl;
        return 1;
    }

    vector<string> program;
    string line;

    while (getline(inputFile, line)) {
        program.push_back(line);
    }

    inputFile.close();

    // Analyze the program
    analyzeProgram(program);

    return 0;
}

