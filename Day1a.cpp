#include <fstream>
#include <iostream>

int main()
{
    std::ifstream file("data/Day1.txt");
    std::string line;
    char const* numberStrings = "0123456789";
    int calibrationSum = 0;

    if (file.is_open())
    {
        while (file)
        {
            std::getline(file, line);

            if (line.size() > 0)
            {
                auto firstNum = line.substr(line.find_first_of(numberStrings), 1);
                auto lastNum = line.substr(line.find_last_of(numberStrings), 1);

                calibrationSum += std::stoi( firstNum + lastNum );
            }
        }
    }

    std::cout << "The sum of calibration values is: " << calibrationSum << std::endl;

    return 0;
}