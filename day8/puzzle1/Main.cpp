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
	
	// In case there is no newline at the end of the file
	if (line != "")
		inputs.push_back(line);

	inputFile.close();
	return inputs;
}

vector<int> getSouth(const vector<string>& forest, int treeX, int treeY)
{
	vector<int> south;

	for (int i = treeY + 1; i < forest.size(); i++)
		south.push_back(forest[i][treeX] - '0');

	return south;
}

TEST(Day8Tests, FindsTreesToSouth)
{
	vector<string> forest
	{
		"30373",
		"25512",
		"65332",
		"33549",
		"35390"
	};

	vector<int> expectedResult = {5, 3, 5};
	EXPECT_EQ(getSouth(forest, 1, 1), expectedResult);
}

vector<int> getNorth(const vector<string>& forest, int treeX, int treeY)
{
	vector<int> north;

	for (int i = 0; i < forest.size() && i < treeY; i++)
		north.push_back(forest[i][treeX] - '0');

	return north;
}

TEST(Day8Tests, FindsTreesToNorth)
{
	vector<string> forest
	{
		"30373",
		"25512",
		"65332",
		"33549",
		"35390"
	};

	vector<int> expectedResult = {3, 5};
	EXPECT_EQ(getNorth(forest, 2, 2), expectedResult);
}

vector<int> getWest(const vector<string>& forest, int treeX, int treeY)
{
	vector<int> west;

	for (int i = 0; i < forest.size() && i < treeX; i++)
		west.push_back(forest[treeY][i] - '0');

	return west;
}

TEST(Day8Tests, FindsTreesToWest)
{
	vector<string> forest
	{
		"30373",
		"25512",
		"65332",
		"33549",
		"35390"
	};

	vector<int> expectedResult = {6, 5};
	EXPECT_EQ(getWest(forest, 2, 2), expectedResult);
}

vector<int> getEast(const vector<string>& forest, int treeX, int treeY)
{
	vector<int> east;

	for (int i = treeX + 1; i < forest.size(); i++)
		east.push_back(forest[treeY][i] - '0');

	return east;
}

TEST(Day8Tests, FindsTreesToEast)
{
	vector<string> forest
	{
		"30373",
		"25512",
		"65332",
		"33549",
		"35390"
	};

	vector<int> expectedResult = {3, 2};
	EXPECT_EQ(getEast(forest, 2, 2), expectedResult);
}

bool isVisible(const vector<string>& forest, int treeX, int treeY)
{
	auto north = getNorth(forest, treeX, treeY);
	auto south = getSouth(forest, treeX, treeY);
	auto east = getEast(forest, treeX, treeY);
	auto west = getWest(forest, treeX, treeY);

	int fails = 0;

	for (auto tree : north)
	{
		if (tree >= (forest[treeY][treeX] - '0'))
		{
			fails++;
			break;
		}
	}

	for (auto tree : south)
	{
		if (tree >= (forest[treeY][treeX] - '0'))
		{
			fails++;
			break;
		}
	}

	for (auto tree : east)
	{
		if (tree >= (forest[treeY][treeX] - '0'))
		{
			fails++;
			break;
		}
	}

	for (auto tree : west)
	{
		if (tree >= (forest[treeY][treeX] - '0'))
		{
			fails++;
			break;
		}
	}

	return (fails < 4);
}

TEST(Day8Tests, HandlesSpecificTree)
{
	vector<string> forest
	{
		"30373",
		"25512",
		"65332",
		"33549",
		"35390"
	};

	EXPECT_EQ(isVisible(forest, 1, 1), true);
	EXPECT_EQ(isVisible(forest, 2, 3), true);
	EXPECT_EQ(isVisible(forest, 3, 3), false);
}

int countVisibleTrees(const vector<string>& forest)
{
	int visible = 0;
	visible += 2 * forest.size();
	visible += 2 * forest[0].length();
	visible -= 4; // Don't count the trees in both x and y

	for (int i = 1; i < forest.size() - 1; i++)
	{
		for (int j = 1; j < forest[i].length() - 1; j++)
			visible += isVisible(forest, j, i);
	}

	return visible;
}

TEST(Day8Tests, HandlesSampleInput)
{
	vector<string> forest
	{
		"30373",
		"25512",
		"65332",
		"33549",
		"35390"
	};

	EXPECT_EQ(countVisibleTrees(forest), 21);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	try
	{
		auto forest = loadInputs("input/inputs.txt");
		cout << "Result: " << countVisibleTrees(forest) << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return RUN_ALL_TESTS();
}
