#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

void parseNumbersFromString(const std::string& numberString, std::vector<int>& numberVector)
{
    // Get part number locations
    int pointer = 0;
    std::string number = "";
    bool parsingNumber = false;

    while (pointer <= numberString.length())
    {
        if (pointer == numberString.length() && parsingNumber)
        {
            numberVector.push_back(std::stoi(number));
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
            numberVector.push_back(std::stoi(number));
            number = "";
        }

        pointer++;
    }
}

int main()
{
    std::ifstream file("data/Day4.txt");
    std::string line;

    std::unordered_map<int, int> cardCounts;

    if (file.is_open())
    {
        int lineNumber = 0;
        while (file)
        {

            std::getline(file, line);

            if (line.length() > 0)
            {
                if (cardCounts.find(lineNumber) == cardCounts.end())
                {
                    cardCounts[lineNumber] = 1;
                }
                else
                {
                    cardCounts[lineNumber]++;
                }

                // Get winning numbers
                std::vector<int> winningNumbers = {};
                parseNumbersFromString(line.substr(line.find('|')), winningNumbers);

                // Get card numbers
                std::vector<int> cardNumbers = {};
                parseNumbersFromString(line.substr(line.find(':'), line.find('|') - line.find(':')), cardNumbers);

                // Determine winning numbers
                int wins = 0;
                for (auto& cardNumber : cardNumbers)
                {
                    if (std::find(winningNumbers.begin(), winningNumbers.end(), cardNumber) != winningNumbers.end())
                    {
                        wins++;
                    }
                }

                for (int copy = 1; copy <= cardCounts[lineNumber]; ++copy)
                {
                    for (int i = lineNumber + 1; i <= lineNumber + wins; ++i)
                    {
                        if (cardCounts.find(i) != cardCounts.end())
                        {
                            cardCounts[i]++;
                        }
                        else
                        {
                            cardCounts[i] = 1;
                        }
                    }
                }

            }
            lineNumber++;
        }
    }

    int numberOfCards = 0;
    for (auto& [card, count] : cardCounts)
    {
        numberOfCards += count;
    }

    std::cout << "The total number of cards is: " << numberOfCards << std::endl;
    return 0;
}