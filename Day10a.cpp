#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NIL
};

Direction& operator++(Direction& direction)
{
    if (direction == Direction::NIL)
    {
        throw std::out_of_range("for Direction& operator++(Direction&)");
    }
    direction = Direction(static_cast< std::underlying_type<Direction>::type >( direction ) + 1);
    return direction;
}

std::tuple<char, size_t, size_t> getPipe(const Direction& direction, const std::vector<std::string>& pipes, const size_t& linePosition, const size_t& lineIndex)
{
    if (direction == Direction::UP)
    {
        return {pipes[linePosition - 1][lineIndex], linePosition - 1, lineIndex};
    }
    else if (direction == Direction::DOWN)
    {
        return {pipes[linePosition + 1][lineIndex], linePosition + 1, lineIndex};
    }
    else if (direction == Direction::LEFT)
    {
        return {pipes[linePosition][lineIndex - 1], linePosition, lineIndex - 1};
    }
    else if (direction == Direction::RIGHT)
    {
        return {pipes[linePosition][lineIndex + 1], linePosition, lineIndex + 1};
    }
}

int main()
{
    std::ifstream file("data/Day10.txt");
    std::string line;

    std::vector<std::string> pipes;
    // Maps from approach direction to continuing direction for each type of pipe
    std::unordered_map<char, std::unordered_map<Direction, Direction>> pipeToDirectionsMap = {{'F', {{Direction::UP, Direction::RIGHT}, {Direction::LEFT, Direction::DOWN}}},
                                                                                              {'J', {{Direction::DOWN, Direction::LEFT}, {Direction::RIGHT, Direction::UP}}},
                                                                                              {'L', {{Direction::DOWN, Direction::RIGHT}, {Direction::LEFT, Direction::UP}}},
                                                                                              {'7', {{Direction::UP, Direction::LEFT}, {Direction::RIGHT, Direction::DOWN}}},
                                                                                              {'|', {{Direction::DOWN, Direction::DOWN}, {Direction::UP, Direction::UP}}},
                                                                                              {'-', {{Direction::LEFT, Direction::LEFT}, {Direction::RIGHT, Direction::RIGHT}}}};
    size_t linePosition;
    size_t lineIndex;

    if (file.is_open())
    {
        size_t lineNumber = 0;
        while (file)
        {
            std::getline(file, line);
            if (line.length() > 0)
            {
                pipes.push_back(line);

                if (size_t sIndex = line.find('S'); sIndex != std::string::npos)
                {
                    linePosition = lineNumber;
                    lineIndex = sIndex;
                }
            }
            lineNumber++;
        }
    }

    // Determine start direction
    Direction direction = Direction::NIL;
    for (Direction testDirection = Direction::UP; testDirection != Direction::NIL; ++testDirection)
    {
        auto [pipe, position, index] = getPipe(testDirection, pipes, linePosition, lineIndex);

        if (pipeToDirectionsMap[pipe].find(testDirection) != pipeToDirectionsMap[pipe].end())
        {
            direction = testDirection;
            break;
        }
    }

    int64_t stepsInLoop = 0;
    while (true)
    {
        auto [nextPipe, nextPosition, nextIndex] = getPipe(direction, pipes, linePosition, lineIndex);

        stepsInLoop++;
        if (nextPipe == 'S')
        {
            break;
        }

        direction = pipeToDirectionsMap[nextPipe][direction];
        linePosition = nextPosition;
        lineIndex = nextIndex;
    }

    std::cout << "The largest number of steps from the starting position is: " << stepsInLoop / 2 << std::endl;
    return 0;
}