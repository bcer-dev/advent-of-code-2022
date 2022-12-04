#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <gtest/gtest.h>
using namespace std;

using ElfGroup = array<string, 3>;

vector<ElfGroup> loadInputs(const string& path)
{
	ifstream inputFile(path);
	if (!inputFile.is_open())
		throw runtime_error("Failed to open input file.");

	vector<ElfGroup> inputs;
	string line;
	int currSize = 0;

	ElfGroup current;
	while (getline(inputFile, line))
	{
		if (currSize == 3)
		{
			inputs.push_back(current);
			currSize = 0;
		}
		current[currSize++] = line;
	}

	inputs.push_back(current);

	inputFile.close();
	return inputs;
}

inline int getPriority(char c)
{
	if (isupper(c))
		return c - 'A' + 27;

	return c - 'a' + 1;
}

int findBadge(const string& r1, const string& r2, const string& r3)
{
	for (auto& c : r1)
	{
		if (r2.find(c) != string::npos && r3.find(c) != string::npos)
			return getPriority(c);
	}
	return -1;
}

TEST(RucksackTests, HandlesSampleInput)
{
	auto badge1 = findBadge(
		"wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
		"ttgJtRGJQctTZtZT",
		"CrZsJsPPZsGzwwsLwLmpwMDw"
	);

	auto badge2 = findBadge(
		"vJrwpWtwJgWrhcsFMMfFFhFp",
		"jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
		"PmmdzqPrVvPwwTWBwg"
	);

	EXPECT_EQ(badge1, 52);
	EXPECT_EQ(badge2, 18);
	EXPECT_EQ(badge1 + badge2, 70);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	try
	{
		auto inputs = loadInputs("input/inputs.txt");

		int total = 0;
		for (const auto& input : inputs)
			total += findBadge(input[0], input[1], input[2]);

		cout << "Total: " << total << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	

	return RUN_ALL_TESTS();
}
