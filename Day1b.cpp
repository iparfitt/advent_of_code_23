#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

int main()
{
    std::ifstream file("data/Day1.txt");
    std::string line;
    std::vector<std::string> numberStrings = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::unordered_map<std::string, int> numberMap = {{"0", 0}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
                                                      {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};
    int calibrationSum = 0;

    if (file.is_open())
    {
        while (file)
        {
            std::getline(file, line);

            if (line.size() > 0)
            {
                size_t firstIdx = line.size();
                size_t lastIdx = 0;

                int firstNum;
                int lastNum;

                // find first and last
                for (auto num : numberStrings)
                {
                    auto idx1 = line.find(num);
                    auto idx2 = line.rfind(num);

                    if (idx1 != std::string::npos)
                    {
                        if (idx1 < firstIdx)
                        {
                            firstIdx = idx1;
                            firstNum = numberMap[num];
                        }
                    }

                    if (idx2 != std::string::npos)
                    {
                        if (idx2 > lastIdx)
                        {
                            lastIdx = idx2;
                            lastNum = numberMap[num];
                        }
                    }
                }

                calibrationSum += std::stoi( std::to_string(firstNum) + std::to_string(lastNum) );
            }
        }
    }

    std::cout << "The sum of calibration values is: " << calibrationSum << std::endl;

    return 0;
}