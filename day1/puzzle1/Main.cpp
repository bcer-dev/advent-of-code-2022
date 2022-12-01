#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

vector<int> loadInputs(const string& path)
{
    ifstream inputFile(path);
    if (!inputFile.is_open())
        throw std::runtime_error("Failed to open file.");

    vector<int> inputs;
    string line;

    int currentCalories = 0;
    while (getline(inputFile, line))
    {
        if (line.empty())
        {
            inputs.push_back(currentCalories);
            currentCalories = 0;
            continue;
        }
        currentCalories += stoi(line);
    }

    if (currentCalories != 0)
        inputs.push_back(currentCalories);

    inputFile.close();
    return inputs;
}

int elfWithMostCalories(const vector<int>& calories)
{
    int maxIndex = 0;

    for (int i = 0; i < calories.size(); i++)
    {
        if (calories[i] > calories[maxIndex])
            maxIndex = i;
    }

    return maxIndex + 1;
}

TEST(ElfCaloriesTests, HandlesValidInput)
{
    EXPECT_EQ(elfWithMostCalories({1000, 2000, 3000, 500, 9100}), 5);
    EXPECT_EQ(elfWithMostCalories({900, 10000, 500, 100}), 2);
}

TEST(ElfCaloriesTests, OutputsFirst)
{
    EXPECT_EQ(elfWithMostCalories({1000, 100, 200, 300, 400}), 1);
    EXPECT_EQ(elfWithMostCalories({900, 100, 200, 400}), 1);
}

TEST(ElfCaloriesTests, OutputsLast)
{
    EXPECT_EQ(elfWithMostCalories({400, 100, 200, 300, 1000}), 5);
    EXPECT_EQ(elfWithMostCalories({400, 300, 600}), 3);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    auto caloriesPerElf = loadInputs("input/inputs.txt");

    auto resultElf = elfWithMostCalories(caloriesPerElf);
    cout << "The elf carrying the most calories (" << caloriesPerElf[resultElf - 1] << ") is elf " << resultElf << ".\n";

    return RUN_ALL_TESTS();
}