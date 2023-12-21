#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

int64_t lowestCommonMultiple(const std::vector<int64_t> numbers)
{
    int64_t multiple = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i)
    {
        multiple = std::lcm(multiple, numbers[i]);
    }
    return multiple;
}

int main()
{
    std::ifstream file("data/Day8.txt");
    std::string line;

    std::string instructions;
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodeToElementsMap;
    std::vector<std::string> startingNodes;

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
                    if (line.substr(2, 1) == "A")
                    {
                        startingNodes.push_back(line.substr(0, 3));
                    }
                }
                lineIndex++;
            }
        }
    }

    size_t totalInstructions = instructions.length();
    size_t index = 0;
    std::vector<int64_t> steps(startingNodes.size(), 0);

    for (auto& node : startingNodes)
    {
        while (true)
        {
            if (instructions[steps[index] % totalInstructions] == 'L')
            {
                node = nodeToElementsMap[node].first;
            }
            else
            {
                node = nodeToElementsMap[node].second;
            }

            steps[index]++;

            if (node.find_last_of('Z') == 2)
            {
                break;
            }
        }
        index++;
    }

    std::cout << "The max steps from AAA to ZZZ are: " << lowestCommonMultiple(steps) << std::endl;
    return 0;
}