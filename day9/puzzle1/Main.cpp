#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <gtest/gtest.h>
#include "util/Vector2D.hpp"
using namespace std;

/**
 * **PLEASE NOTE**
 * This implementation does not work yet.
*/

vector<pair<char, int>> loadInputs(const string& path)
{
	ifstream inputFile(path);
	if (!inputFile.is_open())
		throw runtime_error("Failed to open input file.");

	vector<pair<char, int>> inputs;

	string line;
	while (getline(inputFile, line))
		inputs.push_back({line[0], line[2] - '0'});

	inputFile.close();
	return inputs;
}

TEST(Day9Tests, DistanceTest1)
{
	EXPECT_EQ(Vector2D(0, 1).isTouching({1, 0}), true);
	EXPECT_EQ(Vector2D(1, 1).isTouching({1, 1}), true);

	EXPECT_EQ(Vector2D(0, 0).isTouching({0, 2}), false);
	EXPECT_EQ(Vector2D(0, 0).isTouching({2, 0}), false);
	EXPECT_EQ(Vector2D(-2, 0).isTouching({0, 0}), false);
}

TEST(Day9Tests, DiagonalTest1)
{
	EXPECT_EQ(Vector2D(1, 1).isDiagonalTo({2, 2}), true);
	EXPECT_EQ(Vector2D(2, 2).isDiagonalTo({1, 1}), true);
	EXPECT_EQ(Vector2D(2, 2).isDiagonalTo({3, 3}), true);
	EXPECT_EQ(Vector2D(1, 1).isDiagonalTo({1, 3}), false);
}

int solution(const vector<pair<char, int>>& inputs)
{
	vector<Vector2D> positions;
	Vector2D head {2, 5};
	Vector2D tail {head.x - 1, head.y};

	positions.push_back(tail);
	for (const auto& mv : inputs)
	{
		char dir = mv.first;
		int mag = mv.second;

		for (int i = 0; i < mag; i++)
		{
			if (head.isDiagonalTo(tail))
			{
				if (!tail.isTouching(head))
					tail = head;
				head.move(dir);
			}
			else
			{
				head.move(dir);

				if (!tail.isTouching(head))
				{
					tail.move(dir);
					positions.push_back(tail);
				}
			}
		}
	}

	return positions.size();
}

TEST(Day9Tests, HandlesSampleInput)
{
	vector<pair<char, int>> inputs
	{
		{'R', 4},
		{'U', 4},
		{'L', 3},
		{'D', 1},
		{'R', 4},
		{'D', 1},
		{'L', 5},
		{'R', 2}
	};

	EXPECT_EQ(solution(inputs), 13);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}