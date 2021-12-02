#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::string> readArgs(int argc, char const *argv[]);

int main(int argc, char const *argv[])
{
    auto args = readArgs(argc, argv);
    if(args.empty()) {
        std::cout << "Please enter a valid path for the input data." << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream is(args.at(0));
    int depth = 0, distance = 0, aim = 0;

    std::string direction;
    int amount;

    while(!is.eof())
    {
        is >> direction;
        is >> amount;

        if(direction == "forward") {
            distance += amount;
            depth    += amount * aim;
        }
        else if(direction == "up")   aim -= amount;
        else if(direction == "down") aim += amount;
    }

    std::cout << "Distance: " << distance << std::endl;
    std::cout << "Depth: "    << depth    << std::endl;
    std::cout << "Solution: " << distance * depth << std::endl;

    return EXIT_SUCCESS;
}

std::vector<std::string> readArgs(int argc, char const *argv[])
{
    std::vector<std::string> args;
    for(int i = 1; i < argc; i++)
        args.push_back(argv[i]);

    return args;
}