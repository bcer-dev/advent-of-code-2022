#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <boost/algorithm/string.hpp>
#include <gtest/gtest.h>
using namespace std;

class CrateMover9000
{
private:
	vector<stack<char>> boxStacks;
	vector<string> instructions;

public:
	CrateMover9000() = default;
	void loadData(const string& path);
	void moveCrates();
	void printResult() const;
};

// Load and parse the given inputs.
void CrateMover9000::loadData(const string& path)
{
	ifstream inputFile(path);
	if (!inputFile.is_open())
		throw runtime_error("Failed to open input file.");

	string line;

	// Find the number of stacks
	getline(inputFile, line);
	int numberOfTowers = (line.length() + 1) / 4;
	inputFile.seekg(0, inputFile.beg);

	for (int i = 0; i < numberOfTowers; i++)
		boxStacks.push_back(stack<char>());

	// Load stack data
	while (getline(inputFile, line))
	{
		if (line[1] == '1')
			break;

		for (int i = 1; i < line.length(); i += 4)
		{
			if (line[i] == ' ')
				continue;
			int index = (i - 1) / 4;
			boxStacks[index].push(line[i]);
		}
	}

	// Reverse the stack.
	stack<char> tmp;
	for (auto& st : boxStacks)
	{
		while (!st.empty())
		{
			tmp.push(st.top());
			st.pop();
		}

		st = tmp;
	}

	// Ignore blank line after stacks
	getline(inputFile, line);

	while (getline(inputFile, line))
		instructions.push_back(line);

	inputFile.close();
}

// Executes an instruction.
void CrateMover9000::moveCrates()
{
	for (const auto& instruction : instructions)
	{
		vector<string> tokens;
		boost::split(tokens, instruction, boost::is_any_of(" "));

		int from = stoi(tokens[3]) - 1;
		int to = stoi(tokens[5]) - 1;
		int moves = stoi(tokens[1]);
		
		for (int i = 0; i < moves; i++)
		{
			char val = boxStacks[from].top();
			boxStacks[to].push(val);
			boxStacks[from].pop();
		}
	}
}

void CrateMover9000::printResult() const
{
	for (auto& st : boxStacks)
		cout << st.top();
	cout << '\n';
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	CrateMover9000 mover;
	mover.loadData("input/inputs.txt");
	mover.moveCrates();
	mover.printResult();
	
	return RUN_ALL_TESTS();
}
