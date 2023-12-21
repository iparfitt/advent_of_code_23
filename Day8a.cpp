#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>

int main()
{
    std::ifstream file("data/Day8.txt");
    std::string line;

    std::string instructions;
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodeToElementsMap;

    if (file.is_open())
    {
        int lineIndex = 0;
        while (file)
        {
            std::getline(file, line);
            if (line.length() > 0)
            {
                if (lineIndex == 0)
                {
                    instructions = line;
                }
                else
                {
                    nodeToElementsMap[line.substr(0, 3)] = std::make_pair(line.substr(7, 3), line.substr(12, 3));
                }
                lineIndex++;
            }
        }
    }

    int64_t totalSteps = 0;
    std::string currentNode = "AAA";
    size_t stepIndex = 0;
    size_t totalInstructions = instructions.length();

    while (true)
    {
        if (auto& nextStep = instructions[stepIndex % totalInstructions]; nextStep == 'L')
        {
            currentNode = nodeToElementsMap[currentNode].first;
        }
        else
        {
            currentNode = nodeToElementsMap[currentNode].second;
        }
        totalSteps++;
        stepIndex++;

        if (currentNode == "ZZZ")
        {
            break;
        }
    }

    std::cout << "The total steps from AAA to ZZZ are: " << totalSteps << std::endl;
    return 0;
}