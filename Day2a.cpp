#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<std::string> splitString(const std::string& string, const std::string& delimiter)
{
    std::string stringCopy(string);
    std::vector<std::string> subStrings;
    size_t delimiterLocation;

    while ((delimiterLocation = stringCopy.find(delimiter)) != std::string::npos)
    {
        subStrings.emplace_back(stringCopy.substr(0, delimiterLocation));
        stringCopy.erase(0, delimiterLocation + delimiter.length());
    }
    subStrings.emplace_back(stringCopy);
    return subStrings;
}

int main()
{
    std::ifstream file("data/Day2.txt");
    std::string line;
    int idSum = 0;
    std::unordered_map<std::string, int> maxCounts = {{"red", 12}, {"blue", 14}, {"green", 13}};

    if (file.is_open())
    {
        while (file)
        {
            bool possibleGame = true;
            std::getline(file, line);
            std::string id = line;

            if (line.length() <= 0)
            {
                continue;
            }

            id.erase(id.find(":"));
            id.erase(id.find("Game "), 5);
            line.erase(0, line.find(":") + 2);


            std::vector<std::string> cubeSubsets = splitString(line, "; ");
            for (auto& handful : cubeSubsets)
            {
                std::vector<std::string> cubeCounts = splitString(handful, ", ");

                for (auto& cubes : cubeCounts)
                {
                    std::vector<std::string> count = splitString(cubes, " ");
                    if (std::stoi(count[0]) > maxCounts.at(count[1]))
                    {
                        possibleGame = false;
                        break;
                    }
                }
            }

            if (possibleGame)
            {
                idSum += std::stoi(id);
            }
        }
    }

    std::cout << "The sum of IDs of possible games is: " << idSum << std::endl;

    return 0;
}