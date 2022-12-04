#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
using namespace std;

vector<string> loadInputs(const string& path)
{
	ifstream inputFile(path);
	if (!inputFile.is_open())
		throw runtime_error("Failed to open input file.");

	vector<string> inputs;

	string line;
	while (getline(inputFile, line))
		inputs.push_back(line);

	if (line != "")
		inputs.push_back(line);

	inputFile.close();
	return inputs;
}

char getCommonItem(const string& com1, const string& com2) 
{
	for (auto& c : com1)
	{
		if (com2.find(c) != string::npos)
			return c;
	}
	return 0;
}

inline int getPriority(char c)
{
	if (isupper(c))
		return c - 'A' + 27;

	return c - 'a' + 1;
}

int findError(const string& rucksack)
{
	auto size = rucksack.length() / 2;

	auto com1 = rucksack.substr(0, size);
	auto com2 = rucksack.substr(size);
	auto common = getCommonItem(com1, com2);

	return getPriority(common);
}

TEST(RucksackTests, GivesCorrectPriority)
{
	EXPECT_EQ(getPriority('a'), 1);
	EXPECT_EQ(getPriority('z'), 26);
	EXPECT_EQ(getPriority('A'), 27);
	EXPECT_EQ(getPriority('Z'), 52);
}

TEST(RucksackTests, HandlesSampleInput)
{
	int total = 0;
	auto inputs = {"vJrwpWtwJgWrhcsFMMfFFhFp", "jQHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL"};
	for (const auto& i : inputs)
		total += findError(i);
	EXPECT_EQ(total, 54);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	try
	{
		auto inputs = loadInputs("input/inputs.txt");
		int total = 0;

		for (const auto& input : inputs)
			total += findError(input);

		cout << "Total: " << total << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	

	return RUN_ALL_TESTS();
}
