#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <array>

constexpr int nBits = 12;

std::bitset<nBits> extractRating(std::vector<std::bitset<nBits>> const &list, bool majority, int bitPos = nBits-1);
std::vector<std::string> readArgs(int argc, char const *argv[]);

int main(int argc, char const *argv[])
{
    auto args = readArgs(argc, argv);
    if(args.empty()) return EXIT_FAILURE;

    std::ifstream is(args[0]);
    std::vector<std::bitset<nBits>> input;
    std::string tmp;

    for (int i = 0; !is.eof(); i++)
    {
        is >> tmp;
        input.push_back(std::bitset<nBits>(tmp));
    }

    // Compute gamma
    std::array<int, nBits> amount{ 0 };
    for(auto const &bits : input)
    {
        for(int j = 0; j < nBits; j++)
            amount[j] += bits[j];
    }

    unsigned gamma = 0;
    for(int j = 0; j < nBits; j++)
    {
        if(amount[j] > (input.size()/2))
            gamma |=  1 << j;
    }

    // Compute epsilon
    unsigned epsilon = gamma ^ ( (2 << nBits-1) - 1 );

    // Compute oxygen generator rating
    auto oxygenRating = extractRating(input, true).to_ulong();

    // Compute CO2 scrubber rating
    auto scrubberRating = extractRating(input, false).to_ulong();

    std::cout << "The gamma rate is " << std::bitset<nBits>(gamma).to_string() << " (" << std::dec << gamma << ")" << std::endl;
    std::cout << "The epsilon rate is " << std::bitset<nBits>(epsilon).to_string() << " (" << std::dec << epsilon << ")" << std::endl;
    std::cout << "Their product is " << gamma * epsilon << std::endl << std::endl;

    std::cout << "Oxygen rating is " << oxygenRating << std::endl;
    std::cout << "CO2 scrubber rating is " << scrubberRating << std::endl;
    std::cout << "Their product is " << oxygenRating * scrubberRating << std::endl << std::endl;

    return EXIT_SUCCESS;
}

std::bitset<nBits> extractRating(std::vector<std::bitset<nBits>> const &list, bool majority, int bitPos)
{
    if(list.size() == 1) return list[0];
    else if(bitPos < 0)  return {};
    else
    {
        int majorityBit = 0;
        for(auto const &entry : list)
        {
            majorityBit += entry[bitPos];
        }
        majorityBit = (majorityBit >= list.size()/2) ? 1 : 0;

        std::vector<std::bitset<nBits>> tmp;
        for(auto const &entry : list)
        {
            // if bitPos bit is equal to the majority bit at bitPos
            if(entry[bitPos] == ( majority ? majorityBit : !majorityBit ) )
                tmp.push_back(entry);
        }
        return extractRating(tmp, majority, bitPos - 1);
    }
};


std::vector<std::string> readArgs(int argc, char const *argv[])
{
    std::vector<std::string> args;
    for(int i = 1; i < argc; i++)
        args.push_back(argv[i]);

    return args;
}