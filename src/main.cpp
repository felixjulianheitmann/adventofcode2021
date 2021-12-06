#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

std::vector<std::string> readArgs(int argc, char const *argv[]);
std::vector<std::string> splitString(std::string src, std::string delim);

constexpr int Days = 256;
class LanternFishGroup
{
public:
    LanternFishGroup(long amountOfFish = 1, int startCounter = 8)
        : _counter(startCounter)
        , _amountOfFish(amountOfFish)
    {}

    bool decrCounter()
    {
        if(--_counter < 0) {
            _counter = 6;
            return true;
        }
        return false;
    }
    long addFish(long number) { _amountOfFish+=number; return _amountOfFish; }
    long getAmount() const { return _amountOfFish; }
    int getCounter() const { return _counter; }
private:
    int _counter;
    long _amountOfFish;
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
    std::vector<LanternFishGroup> population;
    for(auto const v : inputs) population.push_back({ 1, std::stoi(v) });

    // Start simulation
    for(int i = 0; i < Days; ++i)
    {
        long newFish = 0;
        std::for_each(
            population.begin(),
            population.end(),
            [&newFish](auto &fish)
            {
                if(fish.decrCounter()) newFish += fish.getAmount();
            }
        );

        population.push_back({ newFish });
        long nFish = std::accumulate<std::vector<LanternFishGroup>::iterator, long>(
            population.begin(),
            population.end(),
            0,
            [](auto const v, auto const &fish){
                return v + fish.getAmount();
            }
        );
        std::cout << "Day " << i+1 << ": " << nFish << std::endl;
    }

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