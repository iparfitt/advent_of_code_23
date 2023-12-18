#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

int getGearRatio(int lineNumber, int location, const std::unordered_map<int, std::vector<int>>& partNumberLocations, std::vector<int> partNumbers)
{
    int adjacentGears = 0;
    int gearRatio = 1;

    for (auto& [index, partLocation] : partNumberLocations)
    {
        if (( partLocation[0] >= ( lineNumber - 1 ) ) && ( partLocation[0] <= ( lineNumber + 1 ) ))
        {
            if ((location >= ( partLocation[1] - 1 )) && (location <= ( partLocation[2] + 1 )))
            {
                adjacentGears++;
                gearRatio *= partNumbers[index];
            }
        }
    }

    if (adjacentGears != 2)
    {
        return 0;
    }
    return gearRatio;
}

int main()
{
    std::ifstream file("data/Day3.txt");
    std::string line;

    int gearRatioSum = 0;

    std::vector<int> partNumbers;
    std::unordered_map<int, std::vector<int>> partNumberIndexToLocationMap; // Location given by line, indexStart, indexEnd
    std::unordered_map<int, std::vector<int>> gearLocations; // Location given by line, index

    if (file.is_open())
    {
        int lineNumber = 0;
        while (file)
        {
            std::getline(file, line);

            if (line.length() > 0)
            {
                // Get symbol locations
                for (int i = 0; i < line.length(); ++i)
                {
                    const char& c = line[i];
                    if (c == '*')
                    {
                        gearLocations[lineNumber].push_back(i);
                    }
                }

                // Get part number locations
                int pointer = 0;
                std::string partNumber = "";
                bool parsingNumber = false;
                int startIndex;

                while (pointer <= line.length())
                {
                    if (pointer == line.length() && parsingNumber)
                    {
                        partNumbers.push_back(std::stoi(partNumber));
                        int partnumberIndex = partNumbers.size() - 1;
                        partNumberIndexToLocationMap[partnumberIndex] = {lineNumber, startIndex, pointer - 1};
                        break;
                    }

                    const char& c = line[pointer];
                    if (isdigit(c))
                    {
                        if (!parsingNumber)
                        {
                            parsingNumber = true;
                            startIndex = pointer;
                        }

                        partNumber += c;
                    }
                    else if (parsingNumber)
                    {
                        parsingNumber = false;
                        partNumbers.push_back(std::stoi(partNumber));

                        int partnumberIndex = partNumbers.size() - 1;
                        partNumberIndexToLocationMap[partnumberIndex] = {lineNumber, startIndex, pointer - 1};

                        startIndex = 0;
                        partNumber = "";
                    }

                    pointer++;
                }
            }
            lineNumber++;
        }
    }

    for (auto& [line, locations] : gearLocations)
    {
        for (auto& location : locations)
        {
            gearRatioSum += getGearRatio(line, location, partNumberIndexToLocationMap, partNumbers);
        }
    }

    std::cout << "The sum of gear ratios is: " << gearRatioSum << std::endl;
    return 0;
}