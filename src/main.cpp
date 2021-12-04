#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>
#include <numeric>

using Cell_t  = std::pair<int, bool>;
using Board_t = std::pair<std::array<std::array<Cell_t, 5>, 5>, bool>;

std::vector<std::string> readArgs(int argc, char const *argv[]);
Board_t transpose(Board_t const &board);


int main(int argc, char const *argv[])
{
    auto args = readArgs(argc, argv);
    if(args.empty()) return EXIT_FAILURE;

    std::ifstream is(args[0]);
    std::string tmp;

    // Read all input numbers.
    is >> tmp;
    std::stringstream tmpStream(tmp);
    std::vector<std::array<char, 3>> inputs;
    for(std::array<char, 3> n; tmpStream.getline(&n[0], 3, ','); )
        inputs.push_back(n);

    std::vector<int> draws;
    for(auto const &item : inputs)
    {
        draws.push_back(std::stol(std::string(&item[0])));
    }

    // Read all boards
    std::vector<Board_t> boards;
    while(!is.eof())
    {
        boards.push_back({});
        auto &board = boards.back();

        for(auto &row : board.first)
        for(auto &cell : row)
                is >> cell.first;
    }

    // Start drawing numbers
    int winningNumber = -1;
    Board_t winningBoard;
    for(auto const draw : draws)
    {
        // Check off on all boards
        for(auto &board : boards)
        for(auto &row   : board.first)
        for(auto &cell  : row)
        {
            if(draw == cell.first) cell.second = true;
        }

        // Check for winner
        auto winningRoutine = 
        [&winningNumber, &winningBoard](int draw, Board_t &board)
        {
            for(auto const &row : board.first)
            {
                if(std::all_of(row.begin(), row.end(), [](auto const &c){ return c.second; }))
                {
                    winningNumber = draw;
                    board.second = true;
                    winningBoard = board;
                    return true;
                }
            }
            return false;
        };

        for(auto &board : boards)
        {
            if(!board.second)
            {
                winningRoutine(draw, board);
                board = transpose(board);
                winningRoutine(draw, board);
            }
        }

        // break if all boards have won
        if(std::all_of(boards.begin(), boards.end(), [](auto const &b){ return b.second; }))
            break;
    }

    // Calculate result value
    int unmarkedSum = 0;
    for(auto const &row : winningBoard.first)
    {
        unmarkedSum += std::accumulate(
            row.begin(),
            row.end(),
            0,
            [](auto const &s, auto const &c)
            {
                if(!c.second) return s+c.first;
                return s;
            }
        );
    }

    std::cout << "Der Ergebniswert ist " << unmarkedSum * winningNumber << std::endl;

    return EXIT_SUCCESS;
}

std::vector<std::string> readArgs(int argc, char const *argv[])
{
    std::vector<std::string> args;
    for(int i = 1; i < argc; i++)
        args.push_back(argv[i]);

    return args;
}

Board_t transpose(Board_t const &board)
{
    Board_t transpose = board;
    for(int i = 0; i < transpose.first.size();    ++i)
    for(int j = 0; j < transpose.first[0].size(); ++j)
    {
        transpose.first[i][j] = board.first[j][i];
    }
    return transpose;
}