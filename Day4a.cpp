#include <algorithm>
#include <fstream>
#include <iostream>
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

    int totalCardsWorth = 0;

    if (file.is_open())
    {
        while (file)
        {

            std::getline(file, line);
            int cardWorth = 0;

            if (line.length() > 0)
            {
                // Get winning numbers
                std::vector<int> winningNumbers = {};
                parseNumbersFromString(line.substr(line.find('|')), winningNumbers);

                // Get card numbers
                std::vector<int> cardNumbers = {};
                parseNumbersFromString(line.substr(line.find(':'), line.find('|') - line.find(':')), cardNumbers);

                // Determine winning numbers
                bool firstWin = true;

                for (auto& cardNumber : cardNumbers)
                {
                    if (std::find(winningNumbers.begin(), winningNumbers.end(), cardNumber) != winningNumbers.end())
                    {
                        if (!firstWin)
                        {
                            cardWorth *= 2;
                        }
                        else
                        {
                            cardWorth += 1;
                            firstWin = false;
                        }
                    }
                }
            }
            totalCardsWorth += cardWorth;
        }
    }

    std::cout << "The worth of the cards is: " << totalCardsWorth << std::endl;
    return 0;
}