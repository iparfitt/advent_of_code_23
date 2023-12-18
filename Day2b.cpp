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
    int powerSum = 0;

    if (file.is_open())
    {
        while (file)
        {
            std::unordered_map<std::string, int> minCubes = {{"red", 0}, {"blue", 0}, {"green", 0}};
            std::getline(file, line);

            if (line.size() <= 0)
            {
                continue;
            }

            line.erase(0, line.find(":") + 2);

            std::vector<std::string> cubeSubsets = splitString(line, "; ");
            for (auto& handful : cubeSubsets)
            {
                std::vector<std::string> cubeCounts = splitString(handful, ", ");

                for (auto& cubes : cubeCounts)
                {
                    std::vector<std::string> count = splitString(cubes, " ");
                    if (std::stoi(count[0]) > minCubes[count[1]])
                    {
                        minCubes[count[1]] = std::stoi(count[0]);
                    }

                }
            }

            powerSum += ( minCubes["red"] * minCubes["blue"] * minCubes["green"] );
        }
    }

    std::cout << "The power sum of the minimum cubes required for games is: " << powerSum << std::endl;

    return 0;
}