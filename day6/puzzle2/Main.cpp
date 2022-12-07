#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <set>
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

	inputFile.close();
	return inputs;
}

int findPacketMarker(const string& key)
{
	constexpr int blockSize = 14;
	for (int i = 0; i < key.length() - blockSize; i++)
	{
		auto block = key.substr(i, blockSize);
		set<char> unique(block.begin(), block.end());
		if (block.length() == unique.size())
			return i + blockSize;
	}

	return -1;
}

TEST(PacketMarkerTests, HandlesSample1)
{
	EXPECT_EQ(findPacketMarker("bvwbjplbgvbhsrlpgdmjqwftvncz"), 23);
}

TEST(PacketMarkerTests, HandlesSample2)
{
	EXPECT_EQ(findPacketMarker("nppdvjthqldpwncqszvftbrmjlhg"), 23);
}

TEST(PacketMarkerTests, HandlesSample3)
{
	EXPECT_EQ(findPacketMarker("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg"), 29);
}

TEST(PacketMarkerTests, HandlesSample4)
{
	EXPECT_EQ(findPacketMarker("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"), 26);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	try
	{
		auto inputs = loadInputs("input/inputs.txt");
		cout << "Result: " << findPacketMarker(inputs[0]) << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	

	return RUN_ALL_TESTS();
}
