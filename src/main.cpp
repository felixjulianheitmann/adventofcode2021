#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> readArgs(int argc, char const *argv[]);
std::vector<std::string> splitString(std::string src, std::string delim);

int main(int argc, char const *argv[])
{
    auto args = readArgs(argc, argv);
    if(args.empty()) return EXIT_FAILURE;

    std::ifstream is(args[0]);

    // template main

    return EXIT_SUCCESS;
}

std::vector<std::string> readArgs(int argc, char const *argv[])
{
    std::vector<std::string> args;
    for(int i = 1; i < argc; i++)
        args.push_back(argv[i]);

    return args;
}


std::vector<std::string> splitString(std::string src, std::string delim)
{
    std::vector<std::string> ret;
    while(true)
    {
        auto pos = src.find(delim, 0);
        ret.push_back(src.substr(0, pos));
        if(pos != std::string::npos)
        {
            src = src.substr(pos + delim.size());
        }
        else
        {
            break;
        }
    }

    return ret;
}