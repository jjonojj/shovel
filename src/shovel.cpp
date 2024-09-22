#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

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
}

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

int eval(std::string &proc) {
    std::vector<std::string> tokens = tokenize(proc);

    std::vector<Function> funcs;
    std::vector<Integer> ints;
    std::vector<String> strings;

    int ptr = 0;

    while (ptr < tokens.size()) {
        std::string token = tokens[ptr];
        // no switch for std::strings, so we use ifs :D

        // expect function
        if (token == "func") {
            Function func;
            func.name = token;

            // increment ptr
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

    eval(proc);
}
