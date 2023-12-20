#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <unordered_map>
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
            numberVector.push_back(std::stoll(number));
            number = "";
        }

        pointer++;
    }
    return numberVector;
}

void parseNumVectorFromStringVector(const std::vector<std::string>& vector, std::vector<std::vector<int64_t>>* ranges)
{
    for (auto& line : vector)
    {
        ranges->push_back(parseNumbersFromString(line));
    }
}

int64_t getOr(const std::vector<std::vector<int64_t>>& ranges, int64_t val)
{
    for (auto& range : ranges)
    {
        if (( val >= range[0] ) &&
            ( val < ( range[0] + range[2] ) ))
        {
            return range[1] + ( val - range[0] );
        }
    }
    return val;
}

bool seedExists(const int64_t seed, const std::vector<int64_t>& seedRanges)
{
    for (size_t i = 0; i < seedRanges.size(); i += 2)
    {
        if (( ( seed - seedRanges[i] ) >= 0 ) && ( ( seed - seedRanges[i] ) < seedRanges[i + 1] ))
        {
            return true;
        }
    }
    return false;
}

int main()
{
    auto startTime = std::chrono::system_clock::now();
    std::ifstream file("data/Day5.txt");
    std::string line;

    std::vector<int64_t> seedNumbers;

    std::vector<std::vector<int64_t>> soilToSeed;
    std::vector<std::vector<int64_t>> fertilizerToSoil;
    std::vector<std::vector<int64_t>> waterToFertilizer;
    std::vector<std::vector<int64_t>> lightToWater;
    std::vector<std::vector<int64_t>> temperatureToLight;
    std::vector<std::vector<int64_t>> humidityToTemperature;
    std::vector<std::vector<int64_t>> humidityToLocation;

    if (file.is_open())
    {
        std::vector<std::string> mappingDetails;
        std::vector<std::vector<int64_t>>* vectorReference = &soilToSeed;
        bool parsingMap = false;
        while (file)
        {
            std::getline(file, line);
            if (line.substr(0, 6) == "seeds:")
            {
                seedNumbers = parseNumbersFromString(line);
            }
            else if (line == "seed-to-soil map:")
            {
                parsingMap = true;
            }
            else if (line == "soil-to-fertilizer map:")
            {
                vectorReference = &fertilizerToSoil;
            }
            else if (line == "fertilizer-to-water map:")
            {
                vectorReference = &waterToFertilizer;
            }
            else if (line == "water-to-light map:")
            {
                vectorReference = &lightToWater;
            }
            else if (line == "light-to-temperature map:")
            {
                vectorReference = &temperatureToLight;
            }
            else if (line == "temperature-to-humidity map:")
            {
                vectorReference = &humidityToTemperature;
            }
            else if (line == "humidity-to-location map:")
            {
                vectorReference = &humidityToLocation;
            }
            else if (parsingMap)
            {
                if (line.length() == 0)
                {
                    parseNumVectorFromStringVector(mappingDetails, vectorReference);
                    mappingDetails = {};
                }
                else
                {
                    mappingDetails.push_back(line);
                }
            }
        }
    }

    int64_t location = 1;
    while (true)
    {
        int64_t seed = getOr(soilToSeed, getOr(
            fertilizerToSoil, getOr(
                waterToFertilizer, getOr(
                    lightToWater, getOr(
                        temperatureToLight, getOr(
                            humidityToTemperature, getOr(
                                humidityToLocation, location)))))));
        if (seedExists(seed, seedNumbers))
        {
            break;
        }

        location++;
    }

    auto endTime = std::chrono::system_clock::now();
    std::cout << "Time to complete was " << std::chrono::duration_cast< std::chrono::microseconds >( endTime - startTime ).count() << std::endl;
    std::cout << "The closest location to plant is: " << location << std::endl;
    return 0;
}