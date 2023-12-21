#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
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
        if (isdigit(c) || c == '-')
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

int64_t findNextNumber(const std::vector<int64_t>& numbers)
{
    std::vector<std::vector<int64_t>> differences;
    differences.push_back(numbers);

    std::vector<int64_t> pastSequence = numbers;
    while (true)
    {
        std::vector<int64_t> sequence;
        for (size_t i = 0; i < pastSequence.size() - 1; ++i)
        {
            sequence.push_back(pastSequence[i + 1] - pastSequence[i]);
        }
        differences.push_back(sequence);

        if (std::all_of(sequence.begin(), sequence.end(), [](int i) { return i==0; }))
        {
            break;
        }
        pastSequence = sequence;
    }

    for (int j = differences.size() - 2; j >= 0; --j)
    {
        int64_t el1 = differences[j + 1].front();
        int64_t el2 = differences[j].front();
        differences[j].insert(differences[j].begin(), el2 - el1);
    }
    return differences[0].front();
}

int main()
{
    std::ifstream file("data/Day9.txt");
    std::string line;

    std::vector<std::vector<int64_t>> patterns;

    if (file.is_open())
    {
        while (file)
        {
            std::getline(file, line);
            if (line.length() > 0)
            {
                patterns.push_back(parseNumbersFromString(line));
            }
        }
    }

    int64_t nextNumberSum = 0;
    for (auto& pattern : patterns)
    {
        nextNumberSum += findNextNumber(pattern);
    }

    std::cout << "The sum of previous numbers in the pattern are: " << nextNumberSum << std::endl;
    return 0;
}