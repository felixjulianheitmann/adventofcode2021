#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <numeric>

std::vector<std::string> readArgs(int, char const *[]);

int main(int argc, char const *argv[])
{
    std::vector<std::string> args = readArgs(argc, argv);
    if(args.size() == 0) return EXIT_FAILURE;

    std::ifstream is;
    is.open(args.at(0));

    std::array<int, 3> window_current, window_prev;
    int slider = 0, increaseCounter = 0;

    // Read in the first 3 values
    for(int &v : window_prev) is >> v;
    window_current = window_prev;

    while (!is.eof())
    {
        is >> window_current[slider];

        int prev = std::accumulate(window_prev.begin(), window_prev.end(), 0);
        int curr = std::accumulate(window_current.begin(), window_current.end(), 0);
        if(prev < curr) increaseCounter++;

        window_prev = window_current;
        slider = ++slider % 3;
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