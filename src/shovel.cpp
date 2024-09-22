#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Options {
    std::string name;
};

Options parseargs(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "error -> not enough arguments specified.";
        exit(1);
    }

    Options opts;
    opts.name = argv[1];

    return opts;
}

std::vector<std::string> tokenize(std::string code) {
    
}

int main(int argc, char** argv) {
    Options opts = parseargs(argc, argv);

    std::string proc;
    std::string filetemp;

    std::ifstream inputfile(opts.name);

    while(getline(inputfile, filetemp)) {
        proc += filetemp;
    }

    std::cout << proc;

    std::cout << "hello shovel!" << argv[1] << std::endl;
}