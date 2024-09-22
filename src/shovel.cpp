#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Options {
    std::string name;
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

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

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

int main(int argc, char **argv) {
    Options opts = parseargs(argc, argv);

    std::string proc;
    std::string filetemp;

    std::ifstream inputfile(opts.name);

    while (getline(inputfile, filetemp)) {
        proc += filetemp;
    }

    std::cout << proc << std::endl;

    std::cout << "tokenized thing: \n";

    std::vector<std::string> tokens = tokenize(proc);

    for (std::string token : tokens) {
        std::cout << "[" << token << "]\n";
    }
}
