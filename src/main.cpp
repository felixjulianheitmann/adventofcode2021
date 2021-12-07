#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <concepts>
#include <type_traits>
#include <numeric>

std::vector<std::string> readArgs(int argc, char const *argv[]);

template <typename T>
requires std::floating_point<T> || std::integral<T>
std::vector<T> splitString(std::string src, std::string delim);

int main(int argc, char const *argv[])
{
    auto args = readArgs(argc, argv);
    if(args.empty()) return EXIT_FAILURE;

    std::ifstream is(args[0]);
    std::string tmp;
    is >> tmp;
    std::vector<int> positions = splitString<int>(tmp, ",");

    // Calculate fuel
    auto [min, max] = std::minmax_element(positions.begin(), positions.end());
    std::pair<int, int> minCost = { -1, std::numeric_limits<int>::max() };
    for (int i = *min; i <= *max; ++i)
    {
        int cost = std::accumulate(
            positions.begin(),
            positions.end(),
            0,
            [i](auto const v, auto const p)
            {
                return v + std::abs(i-p);
            }
        );

        if(cost < minCost.second) minCost = { i, cost };
    }

    std::cout <<
        "Minimal costs are at Position " << minCost.first <<
        " with " << minCost.second << std::endl;


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