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

int pointsGained(char opponent, char player)
{
	opponent -= 'A';
	player -= 'X';

	if (player == opponent)
		return POINTS_PER_DRAW + player + 1;

	if ((opponent + 1) % 3 != player)
		return POINTS_PER_LOSS + player + 1;

	if (player + 'X' == 'X')
		return POINTS_PER_WIN + player + 1;

	if (player + 'X' == 'Y')
		return POINTS_PER_WIN + player + 1;

	if (player + 'X' == 'Z')
		return POINTS_PER_WIN + player + 1;

	return -1;
}

TEST(RockPaperScissorsTests, HandlesMatchOne)
{
	EXPECT_EQ(pointsGained('A', 'Y'), 8);
}

TEST(RockPaperScissorsTests, HandlesMatchTwo)
{
	EXPECT_EQ(pointsGained('B', 'X'), 1);
}

TEST(RockPaperScissorsTests, HandlesMatchThree)
{
	EXPECT_EQ(pointsGained('C', 'Z'), 6);
}

TEST(RockPaperScissorsTests, GivesCorrectTotal)
{
	auto m1 = pointsGained('A', 'Y');
	auto m2 = pointsGained('B', 'X');
	auto m3 = pointsGained('C', 'Z');
	EXPECT_EQ(m1 + m2 + m3, 15);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	try
	{
		auto inputs = loadInputValues("input/inputs.txt");
		int totalPoints = 0;

		for (auto& p : inputs)
			totalPoints += pointsGained(p.first, p.second);

		cout << totalPoints << '\n';
	}
	catch (exception& e)
	{
		cout << e.what() << '\n';
	}

	return RUN_ALL_TESTS();
}
