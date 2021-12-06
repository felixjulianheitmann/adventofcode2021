#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

std::vector<std::string> readArgs(int argc, char const *argv[]);
std::vector<std::string> splitString(std::string src, std::string delim);

constexpr int Days = 80;
class LanternFish
{
public:
    LanternFish(int startCounter = 8) : _counter(startCounter) {};
    bool decrCounter()
    {
        if(--_counter < 0) {
            _counter = 6;
            return true;
        }
        return false;
    }
    int getCounter() const { return _counter; }
    operator int() const { return _counter; }
private:
    int _counter;
};


int main(int argc, char const *argv[])
{
    auto args = readArgs(argc, argv);
    if(args.empty()) return EXIT_FAILURE;

    // Read input
    std::ifstream is(args[0]);
    std::string tmp;
    is >> tmp;
    auto inputs = splitString(tmp, ",");
    std::vector<LanternFish> population;
    for(auto const v : inputs) population.push_back(std::stoi(v));

    // Start simulation
    for(int i = 0; i < Days; ++i)
    {
        int newFish = 0;
        for(auto &fish : population)
        {
            if(fish.decrCounter()) ++newFish;
        }
        population.resize(population.size() + newFish);
    }

    std::cout << "There are " << population.size() << " fish in the sea.";

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