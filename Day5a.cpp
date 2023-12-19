#include <algorithm>
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
            try
            {
                numberVector.push_back(std::stoll(number));
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << " " << number << '\n';
            }

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
        if (( val >= range[1] ) &&
            ( val < ( range[1] + range[2] ) ))
        {
            return range[0] + ( val - range[1] );
        }
    }
    return val;
}

int main()
{
    std::ifstream file("data/Day5.txt");
    std::string line;

    std::vector<int64_t> seedNumbers;
    std::vector<int64_t> locationNumbers;

    std::vector<std::vector<int64_t>> seedToSoil;
    std::vector<std::vector<int64_t>> soilToFertilizer;
    std::vector<std::vector<int64_t>> fertilizerToWater;
    std::vector<std::vector<int64_t>> waterToLight;
    std::vector<std::vector<int64_t>> lightToTemperature;
    std::vector<std::vector<int64_t>> temperatureToHumidity;
    std::vector<std::vector<int64_t>> humidityToLocation;

    if (file.is_open())
    {
        std::vector<std::string> mappingDetails;
        std::vector<std::vector<int64_t>>* vectorReference = &seedToSoil;
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
                vectorReference = &soilToFertilizer;
            }
            else if (line == "fertilizer-to-water map:")
            {
                vectorReference = &fertilizerToWater;
            }
            else if (line == "water-to-light map:")
            {
                vectorReference = &waterToLight;
            }
            else if (line == "light-to-temperature map:")
            {
                vectorReference = &lightToTemperature;
            }
            else if (line == "temperature-to-humidity map:")
            {
                vectorReference = &temperatureToHumidity;
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

    for (auto seed : seedNumbers)
    {
        locationNumbers.push_back(getOr(humidityToLocation, getOr(
            temperatureToHumidity, getOr(
                lightToTemperature, getOr(
                    waterToLight, getOr(
                        fertilizerToWater, getOr(
                            soilToFertilizer, getOr(
                                seedToSoil, seed))))))));
    }
    auto min = std::min_element(locationNumbers.begin(), locationNumbers.end());
    std::cout << "The closest location to plant is: " << *min << std::endl;
    return 0;
}