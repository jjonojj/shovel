#include <cwchar>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <cctype>

enum class ErrorType {
    ERR_UNEXPECTED_TOKEN,
    ERR_MISSING_SEMICOLON
};
void err_exit(ErrorType type, std::string msg) {
    switch (type) {
        case ErrorType::ERR_UNEXPECTED_TOKEN:
            std::cout << "error -> unexpected token: " << msg << std::endl;
            exit(1);
        case ErrorType::ERR_MISSING_SEMICOLON:
            std::cout << "error -> missing semicolon: " << msg << std::endl;
    }
}

struct Options {
    std::string name;
};

struct Integer {
    std::string name;
    int value;
};

struct String {
    std::string name;
    std::string value;
};

struct Function {
    std::string name;
    std::vector<std::string> body;
};

Options parseargs(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "error -> not enough arguments specified.";
        exit(1);
    }

    Options opts;
    opts.name = argv[1];

    return opts;
}

std::vector<std::string> tokenize(const std::string &input) {
    std::vector<std::string> tokens;
    std::string current_token;
    bool in_string = false;

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        if (in_string) {
            current_token += c;
            if (c == '"') {
                tokens.push_back(
                    current_token);
                current_token.clear();
                in_string = false;
            }
            continue;
        }

        if (c == '"') {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
            in_string = true;
            current_token += c;
            continue;
        }

        if (isspace(c)) {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
        } else if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';') {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
            tokens.push_back(
                std::string(1, c));
        } else {
            current_token += c;
        }
    }

    // Add the last token if any
    if (!current_token.empty()) {
        tokens.push_back(current_token);
    }

    return tokens;
}

// example tokens:
// func, main, (, ), {, print, (, "hai :3", ), ;, }

int eval(std::vector<std::string> &proc) {
    std::vector<std::string> tokens = proc;

    std::vector<Function> funcs;
    std::vector<Integer> ints;
    std::vector<String> strings;

    int ptr = 0;

    while (ptr < tokens.size()) {
        bool handled = false;
        bool statement_should_end = false;
        std::string token = tokens[ptr];
        // no switch for std::strings, so we use ifs :D

        // expect function
        if (token == "func") {
            handled = true;
            Function func;
            ptr++;
            func.name = tokens[ptr];
            ptr++;
            if (tokens[ptr] != "(") err_exit(ErrorType::ERR_UNEXPECTED_TOKEN, tokens[ptr]);
            // TODO: arguments
            // ---
            ptr++;
            if (tokens[ptr] != ")") err_exit(ErrorType::ERR_UNEXPECTED_TOKEN, tokens[ptr]);

            ptr++;
            if (tokens[ptr] != "{") err_exit(ErrorType::ERR_UNEXPECTED_TOKEN, tokens[ptr]);

            ptr++;
            while (tokens[ptr] != "}") {
                func.body.push_back(tokens[ptr]);
                ptr++;
            }
            ptr++;

            funcs.push_back(func);
        }

        // print macro (hardcoded) (yes)
        if (token == "*echo") {
            handled = true;
            std::cout << tokens[ptr+1] << std::endl;
            ptr += 2;
        }

        if (!handled) {
            // except a function call (or a macro, if i implement a working macro system)
            if (tokens[ptr+1] != "(") {
                // invalid function call, but i need WAY more error handling :(
            }

            std::string fn_query = token;
            // valid function (i hope)
            ptr+=2;
            while (tokens[ptr] != ")") {
                ptr++;
            }
            ptr++;

            // actually call the function (might need to put this in a function if i implement macros and a std library and blablabla)
            for (Function func : funcs) {
                if (func.name == token) {
                    eval(func.body);
                }
            }
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    Options opts = parseargs(argc, argv);

    std::string proc;
    std::string filetemp;

    std::ifstream inputfile(opts.name);

    while (getline(inputfile, filetemp)) {
        proc += filetemp;
    }
    /*
    std::vector<std::string> temptokens = tokenize(proc);
    for (std::string i : temptokens) {
        std::cout << i << std::endl;
    }
    */

    std::vector<std::string> tokens = tokenize(proc);
    eval(tokens);
}
