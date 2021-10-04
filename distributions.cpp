#include "distributions.hpp"

#include <iomanip>
#include <iostream>
#include <random>
#include <string>

// Assignment 3 Distribution Functions
// Makalee Beelek

// generateUniformDistribution function
// inputs:
//      -howMany: how many integers to randomly generate
//      -min: the minimum number a randomly generated integer can be
//      -max: the maximum number a randomly generated integer can be
//      -numberBins: how many bins to place the numbers in
// outputs:
//      return a DistributionPair vector that is a vector with numberBins
//      amount of bins, each with their specified range and count
// a function that generates howMany random numbers using uniform distribution
// and bins them based on their value
std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins)
{
    // initialize the vector to be returned
    std::vector<DistributionPair> uniformDist;

    // use uniform integer distribution for random number generation
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(min, max);

    // set up the bins and define their range
    for (std::uint8_t i = 0; i < numberBins; i++)
    {

        if (i == 0)
        {
            uniformDist.push_back(DistributionPair(min, i + 1));
        }
        else
        {
            auto previousIndex = i - 1;
            std::uint32_t previousMax = uniformDist[previousIndex].maxValue;
            uniformDist.push_back(DistributionPair(previousMax + 1, previousMax + 2));
        }
    }

    // randomly generate a number and add 1 to the count of the correct bin
    for (std::uint32_t j = 0; j < howMany; j++)
    {
        std::uint32_t randNum = dist(engine);

        for (int k = 0; k < numberBins; k++)
        {
            if (k == 0)
            {
                if (randNum <= uniformDist[k].maxValue)
                {
                    uniformDist[k].count++;
                }
            }
            else if (k == numberBins - 1)
            {
                if (randNum >= uniformDist[k].minValue)
                {
                    uniformDist[k].count++;
                }
            }
            else
            {
                if (randNum >= uniformDist[k].minValue && randNum <= uniformDist[k].maxValue)
                {
                    uniformDist[k].count++;
                }
            }
        }
    }

    // return the correct vector
    return uniformDist;
};

// generateNormalDistribution function
// inputs:
//      -howMany: how many integers to randomly generate
//      -mean: the average of the distribution
//      -stdev: the standard deviation of the distribution
//      -numberBins: how many bins to place the numbers in
// outputs:
//      return a DistributionPair vector that is a vector with numberBins
//      amount of bins, each with their specified range and count
// a function that generates howMany random numbers using normal distribution
// and bins them based on their value
std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins)
{
    // initialize the vector to be returned
    std::vector<DistributionPair> normalDist;

    // get the overall min
    std::uint32_t min = static_cast<std::uint32_t>(mean - (4 * stdev));

    // use uniform integer distribution for random number generation
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::normal_distribution<float> dist(mean, stdev);

    // set up the bins and define their range
    for (std::uint8_t i = 0; i < numberBins; i++)
    {
        if (i == 0)
        {
            normalDist.push_back(DistributionPair(min, min));
        }
        else
        {
            auto previousIndex = i - 1;
            std::uint32_t previousMin = normalDist[previousIndex].minValue;
            normalDist.push_back(DistributionPair(previousMin + 1, previousMin + 1));
        }
    }

    // randomly generate a number and add 1 to the count of the correct bin
    for (std::uint32_t j = 0; j < howMany; j++)
    {
        float randNum = dist(engine);

        for (int k = 0; k < numberBins; k++)
        {
            if (k == 0)
            {
                if (randNum < normalDist[k].maxValue + 1)
                {
                    normalDist[k].count++;
                }
            }
            else if (k == numberBins - 1)
            {
                if (randNum >= normalDist[k].minValue)
                {
                    normalDist[k].count++;
                }
            }
            else
            {
                if (randNum < normalDist[k].maxValue + 1 && randNum >= normalDist[k].minValue)
                {
                    normalDist[k].count++;
                }
            }
        }
    }

    // return the correct vector
    return normalDist;
};

// generatePoissonDistribution function
// inputs:
//      -howMany: how many integers to randomly generate
//      -howOften: goes in as the mean of the distribution
//      -numberBins: how many bins to place the numbers in
// outputs:
//      return a DistributionPair vector that is a vector with numberBins
//      amount of bins, each with their specified range and count
// a function that generates howMany random numbers using poisson distribution
// and bins them based on their value
std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins)
{
    // initialize the vector to be returned
    std::vector<DistributionPair> poissonDist;

    // get the overall min
    std::uint8_t min = 0;

    // use uniform integer distribution for random number generation
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::poisson_distribution<int> dist(howOften);

    // set up the bins and define their range
    for (std::uint8_t i = 0; i < numberBins; i++)
    {
        if (i == 0)
        {
            poissonDist.push_back(DistributionPair(min, min));
        }
        else
        {
            auto previousIndex = i - 1;
            std::uint32_t previousMin = poissonDist[previousIndex].minValue;
            poissonDist.push_back(DistributionPair(previousMin + 1, previousMin + 1));
        }
    }

    // randomly generate a number and add 1 to the count of the correct bin
    for (std::uint32_t j = 0; j < howMany; j++)
    {
        std::uint32_t randNum = dist(engine);

        for (int k = 0; k < numberBins; k++)
        {
            if (k == 0)
            {
                if (randNum <= poissonDist[k].maxValue)
                {
                    poissonDist[k].count++;
                }
            }
            else if (k == numberBins - 1)
            {
                if (randNum >= poissonDist[k].minValue)
                {
                    poissonDist[k].count++;
                }
            }
            else
            {
                if (randNum >= poissonDist[k].minValue && randNum <= poissonDist[k].maxValue)
                {
                    poissonDist[k].count++;
                }
            }
        }
    }

    // return the correct vector
    return poissonDist;
};

// plotDistribution function
// inputs:
//      -title: the title of the distribution
//      -distribution: the vector generated by the distribution functions
//      -maxPlotLineSize: the number of characters to use for the bin that
//                        has the most characters
// a function that plots the distributuion function to the console
void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize)
{
    // Print the title
    std::cout << title << std::endl;

    //get the max bin size
    std::uint32_t maxBin = 0;

    for (int i = 0; i < distribution.size(); i++)
    {
        if (distribution[i].count > maxBin)
        {
            maxBin = distribution[i].count;
        }
    }

    // get the number that represents the value of a character
    // for the plot
    float charVal = static_cast<float>(maxPlotLineSize) / maxBin;

    // plot each value in the distribution
    for (int j = 0; j < distribution.size(); j++)
    {
        std::uint32_t numChar = static_cast<std::uint32_t>(ceil(charVal * distribution[j].count));

        std::cout << "[" << std::setw(3) << distribution[j].minValue << ", " << std::setw(3) << distribution[j].maxValue << "] : ";

        for (std::uint32_t k = 0; k < numChar; k++)
        {
            std::cout << "*";
        }

        std::cout << std::endl;
    }
};