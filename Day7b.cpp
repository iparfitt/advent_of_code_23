#include <algorithm>
#include <fstream>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

enum class HandType
{
    NIL = 0,
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
};

const std::unordered_map<char, int> CARD_TO_VALUE = {{'A', 14},
                                                     {'K', 13},
                                                     {'Q', 12},
                                                     {'T', 10},
                                                     {'9', 9},
                                                     {'8', 8},
                                                     {'7', 7},
                                                     {'6', 6},
                                                     {'5', 5},
                                                     {'4', 4},
                                                     {'3', 3},
                                                     {'2', 2},
                                                     {'J', 1}};

std::vector<std::string> splitString(const std::string& string, const std::string& delimiter)
{
    std::string stringCopy(string);
    std::vector<std::string> subStrings;
    size_t delimiterLocation;

    while (( delimiterLocation = stringCopy.find(delimiter) ) != std::string::npos)
    {
        subStrings.emplace_back(stringCopy.substr(0, delimiterLocation));
        stringCopy.erase(0, delimiterLocation + delimiter.length());
    }
    subStrings.emplace_back(stringCopy);
    return subStrings;
}

HandType getHandType(const std::string& hand)
{
    std::unordered_map<char, int> charOccurrencesMap;
    for (int i = 0; i < hand.size(); i++)
    {
        charOccurrencesMap[hand[i]]++;
    }

    HandType handType = HandType::NIL;

    if (charOccurrencesMap.size() == 1)
    {
        handType = HandType::FIVE_OF_A_KIND;
    }
    else if (charOccurrencesMap.size() == 2)
    {
        if (( charOccurrencesMap.begin()->second == 1 ) || ( charOccurrencesMap.begin()->second == 4 ))
        {
            handType = HandType::FOUR_OF_A_KIND;
        }
        else
        {
            handType = HandType::FULL_HOUSE;
        }
    }
    else if (charOccurrencesMap.size() == 3)
    {
        for (auto& [card, count] : charOccurrencesMap)
        {
            if (count == 3)
            {
                handType = HandType::THREE_OF_A_KIND;
            }
            else if (count == 2)
            {
                handType = HandType::TWO_PAIR;
            }
        }
    }
    else if (charOccurrencesMap.size() == 4)
    {
        handType = HandType::ONE_PAIR;
    }
    else
    {
        handType = HandType::HIGH_CARD;
    }

    if (charOccurrencesMap.find('J') == charOccurrencesMap.end())
    {
        return handType;
    }

    int numJs = charOccurrencesMap['J'];

    if (numJs == 4)
    {
        return HandType::FIVE_OF_A_KIND;
    }
    else if (numJs == 3)
    {
        if (handType == HandType::THREE_OF_A_KIND)
        {
            return HandType::FOUR_OF_A_KIND;
        }
        return HandType::FIVE_OF_A_KIND;
    }
    else if (numJs == 2)
    {
        if (handType == HandType::ONE_PAIR)
        {
            return HandType::THREE_OF_A_KIND;
        }
        else if (handType == HandType::TWO_PAIR)
        {
            return HandType::FOUR_OF_A_KIND;
        }
        return HandType::FIVE_OF_A_KIND;
    }
    else if (numJs == 1)
    {
        if (handType == HandType::FOUR_OF_A_KIND)
        {
            return HandType::FIVE_OF_A_KIND;
        }
        else if (handType == HandType::THREE_OF_A_KIND)
        {
            return HandType::FOUR_OF_A_KIND;
        }
        else if (handType == HandType::TWO_PAIR)
        {
            return HandType::FULL_HOUSE;
        }
        else if (handType == HandType::ONE_PAIR)
        {
            return HandType::THREE_OF_A_KIND;
        }
        return HandType::ONE_PAIR;
    }

    return handType;
}

bool firstHandIsStronger(std::tuple<std::string, int64_t, HandType>& hand1, std::tuple<std::string, int64_t, HandType>& hand2)
{
    auto& [hand1Cards, hand1Bid, hand1Type] = hand1;
    auto& [hand2Cards, hand2Bid, hand2Type] = hand2;

    if (hand1Type == HandType::NIL)
    {
        hand1Type = getHandType(hand1Cards);
    }

    if (hand2Type == HandType::NIL)
    {
        hand2Type = getHandType(hand2Cards);
    }

    if (hand1Type != hand2Type)
    {
        return hand1Type > hand2Type;
    }

    for (size_t i = 0; i < hand1Cards.length(); ++i)
    {
        if (hand1Cards[i] == hand2Cards[i])
        {
            continue;
        }
        return CARD_TO_VALUE.at(hand1Cards[i]) > CARD_TO_VALUE.at(hand2Cards[i]);
    }
    return false;
}

int partition(std::vector<std::tuple<std::string, int64_t, HandType>>& hands, int lowIndex, int highIndex)
{
    auto& pivot = hands[highIndex];
    //Index of smaller element and Indicate
    //the right position of pivot found so far
    int i = lowIndex - 1;

    for (int j = lowIndex; j <= highIndex; j++)
    {
        //If current element is smaller than the pivot
        if (firstHandIsStronger(pivot, hands[j]))
        {
            //Increment index of smaller element
            i++;
            std::swap(hands[i], hands[j]);
        }
    }
    std::swap(hands[i + 1], hands[highIndex]);
    return i + 1;
}

// The Quicksort function Implement

void quickSort(std::vector<std::tuple<std::string, int64_t, HandType>>& hands, int lowIndex, int highIndex)
{
    // when low is less than high
    if (lowIndex < highIndex)
    {
        // pi is the partition return index of pivot
        int pi = partition(hands, lowIndex, highIndex);

        //Recursion Call
        //smaller element than pivot goes left and
        //higher element goes right
        quickSort(hands, lowIndex, pi - 1);
        quickSort(hands, pi + 1, highIndex);
    }
}

int main()
{
    std::ifstream file("data/Day7.txt");
    std::string line;

    std::vector<std::tuple<std::string, int64_t, HandType>> hands;

    if (file.is_open())
    {
        while (file)
        {
            std::getline(file, line);
            if (line.length() > 0)
            {
                std::vector<std::string> split = splitString(line, " ");
                hands.emplace_back(std::make_tuple(split[0], std::stoll(split[1]), HandType::NIL));
            }
        }
    }

    quickSort(hands, 0, hands.size() - 1);

    int64_t totalWinnings = 0;
    for (size_t i = 0; i < hands.size(); ++i)
    {
        totalWinnings += ( i + 1 ) * std::get<1>(hands[i]);
    }

    std::cout << "The total winnings from all hands are: " << totalWinnings << std::endl;
    return 0;
}