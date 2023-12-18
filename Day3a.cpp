#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

bool isPartNumber(const std::vector<int>& location, const std::unordered_map<int, std::vector<int>>& symbolLocations)
{
    int lineBefore = location[0] - 1;
    if (lineBefore == -1)
    {
        lineBefore = 0;
    }

    for (int i = lineBefore; i < location[0] + 2 ; ++i)
    {
        if (symbolLocations.find(i) == symbolLocations.end())
        {
            continue;
        }

        const auto& lineLocations = symbolLocations.at(i);
        for (auto loc : lineLocations)
        {
            if ((loc >= ( location[1] - 1 )) && (loc <= ( location[2] + 1 )))
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    std::ifstream file("data/Day3.txt");
    std::string line;

    int partNumberSum = 0;

    std::vector<int> partNumbers;
    std::unordered_map<int, std::vector<int>> partNumberIndexToLocationMap; // Location given by line, indexStart, indexEnd
    std::unordered_map<int, std::vector<int>> symbolLocations; // Location given by line, index

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
                    if (!( isalpha(c) || isdigit(c) || ( c == '.' ) ))
                    {
                        symbolLocations[lineNumber].push_back(i);
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

    for (auto& [partNumberIndex, location] : partNumberIndexToLocationMap)
    {
        if (isPartNumber(location, symbolLocations))
        {
            // std::cout << partNumbers[partNumberIndex] << " is a part number" << std::endl;
            partNumberSum += partNumbers[partNumberIndex];
        }
        else
        {
            // std::cout << partNumbers[partNumberIndex] << " is NOT a part number" << std::endl;
        }
    }

    std::cout << "The sum of part numbers is: " << partNumberSum << std::endl;
    return 0;
}