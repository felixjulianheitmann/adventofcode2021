#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> readArgs(int, char const *[]);

int main(int argc, char const *argv[])
{
    std::vector<std::string> args = readArgs(argc, argv);
    if(args.size() == 0) return EXIT_FAILURE;

    std::ifstream is;
    is.open(args.at(0));

    int current = 0, previous = 0;
    int increaseCounter = 0;
    if(!is.eof()) is >> previous;

    while (!is.eof())
    {
        is >> current;
        if(current > previous) increaseCounter++;
    }

    std::cout << "There are " << increaseCounter << " measurements exceeding its predecessor." << std::endl;

    return EXIT_SUCCESS;
}

std::vector<std::string> readArgs(int argc, char const *argv[])
{
    std::vector<std::string> args;
    for(int i = 1; i < argc; i++)
        args.push_back(argv[i]);

    return args;
}