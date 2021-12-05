#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <numeric>
#include <algorithm>

std::vector<std::string> readArgs(int argc, char const *argv[]);
std::vector<std::string> splitString(std::string src, std::string delim);

constexpr int FieldSize = 1000;

struct Point
{
    int x = 0; int y = 0;
};


using LineDef = std::array<Point, 2>;
using Field   = std::array<std::array<int, FieldSize>, FieldSize>;

int main(int argc, char const *argv[])
{
    auto args = readArgs(argc, argv);
    if(args.empty()) return EXIT_FAILURE;

    // Parsing the input
    std::ifstream is(args[0]);
    std::string tmp;
    std::vector<LineDef> lines;
    while(!is.eof())
    {
        is >> tmp;
        auto start = splitString(tmp, ",");
        is >> tmp; is >> tmp;
        auto end   = splitString(tmp, ",");
        lines.push_back({ 
            Point{ std::stoi(start[0]), std::stoi(start[1]) },
            Point{ std::stoi(end  [0]), std::stoi(end  [1]) },
        });
    }

    // Enter lines on field
    Field field = {};
    for(auto const &line : lines)
    {
        if(line[0].x == line[1].x) // Vertical line
        {
            auto x = line[0].x;
            auto [min, max] = std::minmax(line[0].y, line[1].y);
            for(int y = min; y <= max; ++y ) ++field[x][y];
        }
        else if(line[0].y == line[1].y) // Horizontal line
        {
            auto y = line[0].y;
            auto [min, max] = std::minmax(line[0].x, line[1].x);
            for(int x = min; x <= max; ++x ) ++field[x][y];

        }
    }

    // Calculate result value
    int result = std::accumulate(
        field.begin(),
        field.end(), 
        0,
        [](auto const &v, auto const &line)
        {
            return v + std::accumulate(
                line.begin(),
                line.end(),
                0,
                [](auto const &v, auto const &c)
                {
                    if(c > 1) return v+1;
                    else      return v;
                }
            );
        }
    );


    std::cout << "There are " << result << " fields where at least 2 lines overlap." << std::endl;
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