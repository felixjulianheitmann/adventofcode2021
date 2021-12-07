#include <iostream>
#include <fstream>
#include <vector>
#include <type_traits>
#include <concepts>

std::vector<std::string> readArgs(int argc, char const *argv[]);

template <typename T>
requires std::floating_point<T> || std::integral<T>
std::vector<T> splitString(std::string src, std::string delim);

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

template <typename T>
requires std::floating_point<T> || std::integral<T>
std::vector<T> splitString(std::string src, std::string delim)
{
    std::vector<T> ret;
    while(true)
    {
        auto pos = src.find(delim, 0);
        auto strVal = src.substr(0, pos);
        // Convert to appropriate type
        if constexpr (std::is_integral<T>())
            if constexpr (std::is_signed<T>())
                ret.push_back(std::stol(strVal));
            else
                ret.push_back(std::stoul(strVal));
        else
            ret.push_back(std::stod(strVal));


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