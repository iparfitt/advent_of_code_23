#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<int64_t> parseNumbersFromString(const std::string& numberString)
{
    // Get part number locations
    int64_t pointer = 0;
    std::string number = "";
    bool parsingNumber = false;
    std::vector<int64_t> numberVector;

    while (pointer <= numberString.length())
    {
        if (pointer == numberString.length() && parsingNumber)
        {
            numberVector.push_back(std::stoll(number));
            break;
        }

        const char& c = numberString[pointer];
        if (isdigit(c))
        {
            if (!parsingNumber)
            {
                parsingNumber = true;
            }

            number += c;
        }
        else if (parsingNumber)
        {
            parsingNumber = false;
            numberVector.push_back(std::stoll(number));
            number = "";
        }

        pointer++;
    }
    return numberVector;
}

int main()
{
    std::ifstream file("data/Day6.txt");
    std::string line;

    std::vector<int64_t> raceMilliseconds;
    std::vector<int64_t> recordMillimeters;

    if (file.is_open())
    {
        while (file)
        {
            std::getline(file, line);
            if (line.substr(0, 4) == "Time")
            {
                raceMilliseconds = parseNumbersFromString(line);
            }
            else if (line.substr(0, 8) == "Distance")
            {
                recordMillimeters = parseNumbersFromString(line);
            }
        }
    }

    int64_t multipliedWins = 1;
    for (size_t raceIndex = 0; raceIndex < raceMilliseconds.size(); ++raceIndex)
    {
        int numWins = 0;
        for (int millisecondsHeld = 0; millisecondsHeld <= raceMilliseconds[raceIndex]; ++millisecondsHeld)
        {
            if (( millisecondsHeld * ( raceMilliseconds[raceIndex] - millisecondsHeld ) ) > recordMillimeters[raceIndex])
            {
                numWins++;
            }
        }
        multipliedWins *= numWins;
    }

    std::cout << "The multiplied number of ways you can beat the race are: " << multipliedWins << std::endl;
    return 0;
}