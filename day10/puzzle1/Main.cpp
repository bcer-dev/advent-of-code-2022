#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "CPU.hpp"
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

	return inputs;
}

inline int getSignalStrength(int cycle, int signal)
{
	return cycle * signal;
}

inline Instructions parseInstruction(const string& op)
{
	if (op == "noop")
		return Instructions::NoOp;
	return Instructions::AddX;
}

int sumOfSignalStrengths(const vector<string>& inputs)
{
	int sum = 0;
	CPU processor;

	for (const auto& input : inputs)
	{
		auto instruction = parseInstruction(input);
		auto requiredCycles = static_cast<int>(instruction);

		for (int i = 0; i < requiredCycles; i++)
		{
			auto cycles = processor.getCycles();
			auto x = processor.getX();
			
			if (((cycles + 1) - 20) % 40 == 0)
			{
				sum += (cycles + 1) * x;
			}

			processor.tick();
		}

		if (instruction == Instructions::AddX)
		{
			int space = input.find(' ');
			int v = stoi(input.substr(space + 1));
			processor.addX(v);
		}
	}

	return sum;
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	
	try
	{
		auto inputs = loadInputs("input/inputs.txt");
		int sum = sumOfSignalStrengths(inputs);
		cout << "Result: " << sum << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	

	return RUN_ALL_TESTS();
}
