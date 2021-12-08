#include <iostream>
#include <fstream>
#include <vector>
#include <type_traits>
#include <concepts>
#include <array>
#include <numeric>

std::vector<std::string> readArgs(int argc, char const *argv[]);

using DigitDef = std::array<std::string, 10>;
using DigitVal = std::array<std::string, 4>;

template <typename T>
requires std::floating_point<T> || std::integral<T> || std::same_as<T, std::string>
std::vector<T> splitString(std::string src, std::string delim);

int main(int argc, char const *argv[])
{
    auto args = readArgs(argc, argv);
    if(args.empty()) return EXIT_FAILURE;

    // Read in inputs
    std::ifstream is(args[0]);
    std::vector<std::pair<DigitDef, DigitVal>> inputs;
    for(std::string tmp; std::getline(is, tmp); )
    {
        auto tmpVec = splitString<std::string>(tmp, " ");
        inputs.push_back({});
        std::copy(tmpVec.begin(),      tmpVec.begin()+10, inputs.back().first.begin());
        std::copy(tmpVec.begin() + 11, tmpVec.begin()+15, inputs.back().second.begin());
    }

    // Compute the number of 1,4,7 and 8 in the values

    int amount = std::accumulate(
        inputs.begin(),
        inputs.end(),
        0,
        [](auto const v, auto const line)
        {
            return v + std::accumulate(
                line.second.begin(),
                line.second.end(),
                0,
                [](auto const v, auto const digit)
                {
                    if(    digit.size() == 2 // digit 1
                        || digit.size() == 4 // digit 4
                        || digit.size() == 3 // digit 7
                        || digit.size() == 7 // digit 8
                        ) return v + 1;
                    else return v;
                }
            );
        }
    );

    std::cout << "The amount of 1, 4, 7, and 8 is " << amount << std::endl;

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
requires std::floating_point<T> || std::integral<T> || std::same_as<T, std::string>
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
        else if constexpr (std::is_same<T, std::string>())
            ret.push_back(strVal);
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