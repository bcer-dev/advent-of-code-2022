#include <iostream>
#include <fstream>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

constexpr int POINTS_PER_WIN = 6;
constexpr int POINTS_PER_DRAW = 3;
constexpr int POINTS_PER_LOSS = 0;

vector<pair<char, char>> loadInputValues(const string& path)
{
	ifstream inputFile(path);
	if (!inputFile.is_open())
		throw runtime_error("Failed to open input file.");

	vector<pair<char, char>> inputs;

	string line;
	while (getline(inputFile, line))
		inputs.push_back({line[0], line[2]});

	if (line != "")
		inputs.push_back({line[0], line[2]});

	inputFile.close();
	return inputs;
}

int pointsGained(char opponent, char result)
{
	// Lose
	if (result == 'X')
		return POINTS_PER_LOSS + (opponent - 'A' + 2) % 3 + 1;

	// Draw
	if (result == 'Y')
		return POINTS_PER_DRAW + opponent - 'A' + 1;

	// Win
	return POINTS_PER_WIN + (opponent - 'A' + 1) % 3 + 1;		
}

TEST(RockPaperScissorsTests, HandlesRoundOne)
{
	EXPECT_EQ(pointsGained('A', 'Y'), 4);
}

TEST(RockPaperScissorsTests, HandlesRoundTwo)
{
	EXPECT_EQ(pointsGained('B', 'X'), 1);
}

TEST(RockPaperScissorsTests, HandlesRoundThree)
{
	EXPECT_EQ(pointsGained('C', 'Z'), 7);
}

TEST(RockPaperScissorsTests, GivesCorrectTestResponse)
{
	auto m1 = pointsGained('A', 'Y');
	auto m2 = pointsGained('B', 'X');
	auto m3 = pointsGained('C', 'Z');
	EXPECT_EQ(m1 + m2 + m3, 12);
}

TEST(RockPaperScissorsTests, MiscellaneousTests)
{
	EXPECT_NE(pointsGained('A', 'X'), 0);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	try
	{
		auto inputs = loadInputValues("input/inputs.txt");
		int totalPoints = 0;

		for (const auto& entry : inputs)
			totalPoints += pointsGained(entry.first, entry.second);

		cout << "Result: " << totalPoints << " pts\n";
	}
	catch(const std::exception& e)
	{
		cerr << e.what() << '\n';
	}
	
	return RUN_ALL_TESTS();
}
