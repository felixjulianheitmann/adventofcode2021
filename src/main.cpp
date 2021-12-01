#include <iostream>
#include <vector>

std::vector<std::string> readArgs(int argc, char const *argv[]);

int main(int argc, char const *argv[])
{
    // This is a template main
    return 0;
}

std::vector<std::string> readArgs(int argc, char const *argv[])
{
    std::vector<std::string> args;
    for(int i = 1; i < argc; i++)
        args.push_back(argv[i]);

    return args;
}