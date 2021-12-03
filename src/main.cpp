#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <array>

std::vector<std::string> readArgs(int argc, char const *argv[]);

constexpr int nBits = 12;

int main(int argc, char const *argv[])
{
    auto args = readArgs(argc, argv);
    if(args.empty()) return EXIT_FAILURE;

    std::ifstream is(args[0]);
    std::string tmp;
    std::array<int, nBits> amount{ 0 };
    int i;

    for (i = 0; !is.eof(); i++)
    {
        is >> tmp;
        std::bitset<nBits> bits(tmp);
        for(int j = 0; j < nBits; j++)
            amount[j] += bits[j];
    }

    unsigned gamma = 0;
    for(int j = 0; j < nBits; j++)
    {
        if(amount[j] > (i/2))
            gamma |=  1 << j;
    }
    unsigned epsilon = gamma ^ ( (2 << nBits-1) - 1 );

    std::cout << "The gamma rate is " << std::bitset<nBits>(gamma).to_string() << " (" << std::dec << gamma << ")" << std::endl;
    std::cout << "The epsilon rate is " << std::bitset<nBits>(epsilon).to_string() << " (" << std::dec << epsilon << ")" << std::endl;
    std::cout << "Their product is " << gamma * epsilon << std::endl;

    return EXIT_SUCCESS;
}

std::vector<std::string> readArgs(int argc, char const *argv[])
{
    std::vector<std::string> args;
    for(int i = 1; i < argc; i++)
        args.push_back(argv[i]);

    return args;
}