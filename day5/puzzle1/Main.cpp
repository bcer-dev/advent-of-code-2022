#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <boost/algorithm/string.hpp>
#include <gtest/gtest.h>
using namespace std;

class CrateMover2000
{
private:
	vector<queue<string>> boxStacks;
	vector<string> instructions;

public:
	CrateMover2000() = default;
	void loadData(const string& path);
	void moveCrates(const std::string& instruction);
	void printResult();
};

// Load and parse the given inputs.
void CrateMover2000::loadData(const string& path)
{
	ifstream inputFile(path);
	if (!inputFile.is_open())
		throw runtime_error("Failed to open input file.");
	inputFile.close();
}

// Executes an instruction.
void CrateMover2000::moveCrates(const std::string& instruction)
{
	// auto tokens = boost::split(instruction, ' ');

	// int numberOfBoxes = stoi(tokens[1]);
	// int from = stoi(tokens[3]) - 1;
	// int to = stoi(tokens[5]) - 1;

	// for (int i = 0; i < numberOfBoxes; i++)
	// {
	// 	boxStacks[to].push(boxStacks[from].front());
	// 	boxStacks[from].pop();
	// }
}

void CrateMover2000::printResult()
{
	for (auto& st : boxStacks)
		cout << st.front();
	cout << '\n';
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	CrateMover2000 mover;
	mover.loadData("input/test1.txt");
	return RUN_ALL_TESTS();
}
