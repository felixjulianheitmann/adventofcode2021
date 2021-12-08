#include <iostream>
#include <fstream>
#include <vector>
#include <type_traits>
#include <concepts>
#include <array>
#include <numeric>
#include <map>

// ##### Function declarations ###########################################

std::vector<std::string> readArgs(int argc, char const *argv[]);

template <typename T>
requires std::floating_point<T> || std::integral<T> || std::same_as<T, std::string>
std::vector<T> splitString(std::string src, std::string delim);

template <int N>
std::string getStringOfSize(std::array<std::string, N> const &strings, int size, int nth = 1);

std::string getCharSame(std::string const &a, std::string const &b, bool inverse = false);

bool contains(std::string const &s, char c) { return s.find(c) != std::string::npos; }

int stringToDigit(std::string const &s);

// ##### Type definitions ################################################

using DigitDef = std::array<std::string, 10>;
using DigitVal = std::array<std::string, 4>;


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

    // Decode the inputs
    int resultValue = 0;

    for(auto [definition, value] : inputs)
    {
        std::map<char, char> wiring;
        auto str1 = getStringOfSize<10>(definition, 2);
        auto str7 = getStringOfSize<10>(definition, 3);
        auto str4 = getStringOfSize<10>(definition, 4);
        auto str8 = getStringOfSize<10>(definition, 7);

        std::array<std::string, 3> str690 = {
            getStringOfSize<10>(definition, 6, 1),
            getStringOfSize<10>(definition, 6, 2),
            getStringOfSize<10>(definition, 6, 3),
        };

        std::array<std::string, 3> str235 = {
            getStringOfSize<10>(definition, 5, 1),
            getStringOfSize<10>(definition, 5, 2),
            getStringOfSize<10>(definition, 5, 3),
        };

        wiring[getCharSame(str7, str1, true).front()] = 'd';
        std::string ef = getCharSame(str4, str1, true);
        std::string gc = getCharSame(str8, str4 + str7, true);

        char g, e;

        for(auto const &digit : str235 )
        {
            auto gtmp = getCharSame(gc, digit, true);
            auto ctmp = getCharSame(gc, digit);
            auto etmp = getCharSame(ef, digit, true);
            auto ftmp = getCharSame(ef, digit);
            if(!etmp.empty())
            {
                wiring[etmp.front()] = 'e';
                wiring[ftmp.front()] = 'f';
                e = etmp.front();
            }
            if(!gtmp.empty())
            {
                wiring[gtmp.front()] = 'g';
                wiring[ctmp.front()] = 'c';
                g = gtmp.front();
            }
        }

        for(auto const &digit : str235 )
        {
            if(contains(digit, e))
            {
                wiring[getCharSame(digit, str1).front()] = 'b';
            }
            if(contains(digit, g))
            {
                wiring[getCharSame(digit, str1).front()] = 'a';
            }
        }

        // Transform wiring to correct wiring
        int valueInt = 0;
        for(int i = 0; i < value.size(); ++i)
        {
            std::string trueValue;
            for(auto c : value[i])
            {
                trueValue.push_back(wiring[c]);
            }
            int tmp = stringToDigit(trueValue);
            for(int p = 3-i; p > 0; --p) tmp *= 10;
            valueInt += tmp;
        }

        resultValue += valueInt;

    }

    std::cout << "The resulting value is " << resultValue << std::endl;

    return EXIT_SUCCESS;
}

// ##### Helper functions ########################################################

std::vector<std::string> readArgs(int argc, char const *argv[])
{
    std::vector<std::string> args;
    for(int i = 1; i < argc; i++)
        args.push_back(argv[i]);

    return args;
}

// -------------------------------------------------------------------------------------------

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

// -------------------------------------------------------------------------------------------

template <int N>
std::string getStringOfSize(std::array<std::string, N> const &strings, int size, int nth)
{
    int encounter = 1;
    for(auto const s : strings)
    {
        if(s.size() == size)
        {
            if(encounter == nth) return s;
            else ++encounter;
        }
    }

    return "";
}

// -------------------------------------------------------------------------------------------

// Returns the chars in a that are in b
std::string getCharSame(std::string const &a, std::string const &b, bool inverse)
{
    std::string tmp;
    for(char ca: a)
    {
        if(inverse)
        {
            if( !contains(b, ca) ) tmp.push_back(ca);
        }
        else
        {
            if( contains(b, ca) ) tmp.push_back(ca);
        }

    }
    return tmp;
}

// -------------------------------------------------------------------------------------------

/**
 * A string of up to 7 chars will transformed to a digit 0-9
 * with the following map
 *  dddd
 * e    a
 * e    a
 *  ffff
 * g    b
 * g    b
 *  cccc
 */

int stringToDigit(std::string const &s)
{
    if( contains(s, 'a') &&
        contains(s, 'b') &&
       !contains(s, 'c') &&
       !contains(s, 'd') &&
       !contains(s, 'e') &&
       !contains(s, 'f') &&
       !contains(s, 'g') ) return 1;
    else if(
        contains(s, 'a') &&
       !contains(s, 'b') &&
        contains(s, 'c') &&
        contains(s, 'd') &&
       !contains(s, 'e') &&
        contains(s, 'f') &&
        contains(s, 'g') ) return 2;
    else if(
        contains(s, 'a') &&
        contains(s, 'b') &&
        contains(s, 'c') &&
        contains(s, 'd') &&
       !contains(s, 'e') &&
        contains(s, 'f') &&
       !contains(s, 'g') ) return 3;
    else if(
        contains(s, 'a') &&
        contains(s, 'b') &&
       !contains(s, 'c') &&
       !contains(s, 'd') &&
        contains(s, 'e') &&
        contains(s, 'f') &&
       !contains(s, 'g') ) return 4;
    else if(
       !contains(s, 'a') &&
        contains(s, 'b') &&
        contains(s, 'c') &&
        contains(s, 'd') &&
        contains(s, 'e') &&
        contains(s, 'f') &&
       !contains(s, 'g') ) return 5;
    else if(
       !contains(s, 'a') &&
        contains(s, 'b') &&
        contains(s, 'c') &&
        contains(s, 'd') &&
        contains(s, 'e') &&
        contains(s, 'f') &&
        contains(s, 'g') ) return 6;
    else if(
        contains(s, 'a') &&
        contains(s, 'b') &&
       !contains(s, 'c') &&
        contains(s, 'd') &&
       !contains(s, 'e') &&
       !contains(s, 'f') &&
       !contains(s, 'g') ) return 7;
    else if(
        contains(s, 'a') &&
        contains(s, 'b') &&
        contains(s, 'c') &&
        contains(s, 'd') &&
        contains(s, 'e') &&
        contains(s, 'f') &&
        contains(s, 'g') ) return 8;
    else if(
        contains(s, 'a') &&
        contains(s, 'b') &&
        contains(s, 'c') &&
        contains(s, 'd') &&
        contains(s, 'e') &&
        contains(s, 'f') &&
       !contains(s, 'g') ) return 9;
    else if(
        contains(s, 'a') &&
        contains(s, 'b') &&
        contains(s, 'c') &&
        contains(s, 'd') &&
        contains(s, 'e') &&
       !contains(s, 'f') &&
        contains(s, 'g') ) return 0;
    else return -1;
}
