#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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

int sumOfTopThreeElves(vector<int>& calories)
{
    sort(calories.begin(), calories.end(), greater<int>());
    return calories[0] + calories[1] + calories[2];
}

TEST(ElfCaloriesTests, HandlesSampleInput)
{
    vector<int> testVals = {6000, 4000, 11000, 24000, 10000};
    EXPECT_EQ(sumOfTopThreeElves(testVals), 45000);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    auto inputs = loadInputs("input/inputs.txt");
    auto sum = sumOfTopThreeElves(inputs);
    cout << sum << '\n';

    return RUN_ALL_TESTS();
}