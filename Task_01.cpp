#include<bits/stdc++.h>
using namespace std;

const unordered_set<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "inline", "int", "long", "register", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while", "class", "public",
    "private", "protected", "template", "typename", "using", "namespace",
    "try", "catch", "throw", "bool", "nullptr", "virtual", "override",
    "final", "constexpr", "consteval", "concept", "string"
};

const unordered_set<string> operators = {
    "+", "-", "*", "/", "%", "++", "--", "==", "!=", ">", "<", ">=", "<=",
    "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "=", "+=", "-=", "*=",
    "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", "->", ".", "?", ":", "::"
};

bool isKeyword(const string &token) {
    return keywords.find(token) != keywords.end();
}

bool isOperator(const string &token) {
    return operators.find(token) != operators.end();
}

bool isPunctuation(char c) {
    static const unordered_set<char> operatorChars = {
        '+', '-', '*', '/', '%', '=', '!', '>', '<', '&', '|', '^', '~', '.', '?', ':', '-'
    };
    return ispunct(static_cast<unsigned char>(c)) && (operatorChars.find(c) == operatorChars.end());
}

bool isValidIdentifier(const string &token) {
    if (token.empty()) return false;
    if (!(isalpha(token[0]) || token[0] == '_')) return false;
    for (char c : token) {
        if (!(isalnum(c) || c == '_')) return false;
    }
    return true;
}

bool isNumber(const string &token) {
    int dotCount = 0;
    int start = 0;
    if (token.empty()) return false;
    if (token[0] == '+' || token[0] == '-') start = 1;
    bool digitFound = false;
    for (size_t i = start; i < token.size(); ++i) {
        if (isdigit(token[i])) {
            digitFound = true;
        } else if (token[i] == '.') {
            dotCount++;
            if (dotCount > 1) return false;
        } else {
            return false;
        }
    }
    return digitFound;
}

vector<string> tokenize(const string &line, bool &inBlockComment) {
    vector<string> tokens;
    string temp;
    size_t i = 0, len = line.size();
    bool inString = false, inChar = false;

    while (i < len) {
        if (inBlockComment) {
            if (i + 1 < len && line[i] == '*' && line[i + 1] == '/') {
                inBlockComment = false;
                i += 2;
            } else {
                i++;
            }
            continue;
        }

        char c = line[i];

        if (!inString && !inChar && i + 1 < len && line[i] == '/' && line[i + 1] == '/') {
            if (!temp.empty()) {
                tokens.push_back(temp);
                temp.clear();
            }
            break;
        }

        if (!inString && !inChar && i + 1 < len && line[i] == '/' && line[i + 1] == '*') {
            if (!temp.empty()) {
                tokens.push_back(temp);
                temp.clear();
            }
            inBlockComment = true;
            i += 2;
            continue;
        }

        if (c == '"' && !inChar) {
            if (!inString) {
                if (!temp.empty()) {
                    tokens.push_back(temp);
                    temp.clear();
                }
                inString = true;
                temp.push_back(c);
            } else {
                temp.push_back(c);
                tokens.push_back(temp);
                temp.clear();
                inString = false;
            }
            i++;
            continue;
        }

        if (c == '\'' && !inString) {
            if (!inChar) {
                if (!temp.empty()) {
                    tokens.push_back(temp);
                    temp.clear();
                }
                inChar = true;
                temp.push_back(c);
            } else {
                temp.push_back(c);
                tokens.push_back(temp);
                temp.clear();
                inChar = false;
            }
            i++;
            continue;
        }

        if (inString || inChar) {
            if (c == '\\' && i + 1 < len) {
                temp.push_back(c);
                temp.push_back(line[i + 1]);
                i += 2;
            } else {
                temp.push_back(c);
                i++;
            }
            continue;
        }

        if (isspace(c)) {
            if (!temp.empty()) {
                tokens.push_back(temp);
                temp.clear();
            }
            i++;
            continue;
        }

        bool opFound = false;
        for (int oplen = 3; oplen >= 1; oplen--) {
            if (i + oplen <= len) {
                string opCandidate = line.substr(i, oplen);
                if (isOperator(opCandidate)) {
                    if (!temp.empty()) {
                        tokens.push_back(temp);
                        temp.clear();
                    }
                    tokens.push_back(opCandidate);
                    i += oplen;
                    opFound = true;
                    break;
                }
            }
        }
        if (opFound) continue;

        if (isPunctuation(c)) {
            if (!temp.empty()) {
                tokens.push_back(temp);
                temp.clear();
            }
            tokens.push_back(string(1, c));
            i++;
            continue;
        }

        temp.push_back(c);
        i++;
    }

    if (!temp.empty())
        tokens.push_back(temp);

    return tokens;
}

int main() {
    string filename = "file.txt";
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return 1;
    }

    bool inBlockComment = false;
    string line;

    while (getline(fin, line)) {
        vector<string> tokens = tokenize(line, inBlockComment);
        for (const string &token : tokens) {
            if (isKeyword(token)) {
                cout << "Keyword: " << token << '\n';
            } else if (isOperator(token)) {
                cout << "Operator: " << token << '\n';
            } else if (token.size() == 1 && isPunctuation(token[0])) {
                cout << "Punctuation: " << token << '\n';
            } else if (token.front() == '"' && token.back() == '"' && token.size() >= 2) {
                cout << "String Literal: " << token << '\n';
            } else if (token.front() == '\'' && token.back() == '\'' && token.size() >= 3) {
                cout << "Char Literal: " << token << '\n';
            } else if (isNumber(token)) {
                cout << "Numeric Constant: " << token << '\n';
            } else if (isValidIdentifier(token)) {
                cout << "Valid Identifier: " << token << '\n';
            } else {
                cout << "Invalid Token: " << token << '\n';
            }
        }
    }

    fin.close();
    return 0;
}
