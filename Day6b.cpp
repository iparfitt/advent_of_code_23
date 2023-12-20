#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int64_t parseAllNumbersFromString(const std::string& numberString)
{
    // Get part number locations
    int64_t pointer = 0;
    std::string parsedNumber = "";
    int64_t number;

    while (pointer <= numberString.length())
    {
        if (pointer == numberString.length())
        {
            number = std::stoll(parsedNumber);
            break;
        }

        const char& c = numberString[pointer];
        if (isdigit(c))
        {
            parsedNumber += c;
        }
        pointer++;
    }
    return number;
}

int main()
{
    std::ifstream file("data/Day6.txt");
    std::string line;

    int64_t raceMilliseconds;
    int64_t recordMillimeters;

    if (file.is_open())
    {
        while (file)
        {
            std::getline(file, line);
            if (line.substr(0, 4) == "Time")
            {
                raceMilliseconds = parseAllNumbersFromString(line);
            }
            else if (line.substr(0, 8) == "Distance")
            {
                recordMillimeters = parseAllNumbersFromString(line);
            }
        }
    }

    int64_t numWins = 0;
    for (int millisecondsHeld = 0; millisecondsHeld <= raceMilliseconds; ++millisecondsHeld)
    {
        if (( millisecondsHeld * ( raceMilliseconds - millisecondsHeld ) ) > recordMillimeters)
        {
            numWins++;
        }
    }

    std::cout << "The number of ways you can beat the race are: " << numWins << std::endl;
    return 0;
}