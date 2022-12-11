#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
using namespace std;

enum class InstructionType { NoOp, AddX };

struct Instruction
{
	InstructionType type {};
	int value {};
	static Instruction parse(const string& op);
};

Instruction Instruction::parse(const string& op)
{
	if (op.find("noop") != string::npos)
	{
		return { InstructionType::NoOp, 0 };
	}

	auto space = op.find(' ');
	auto val = stoi(op.substr(space + 1));
	return { InstructionType::AddX, val };
}

vector<Instruction> loadInputs(const string& path)
{
	ifstream inputFile(path);

	if (!inputFile.is_open())
		throw runtime_error("Failed to open input file.");

	vector<Instruction> inputs;

	string line;
	while (getline(inputFile, line))
	{
		inputs.push_back(Instruction::parse(line));
	}

	return inputs;
}

int countSignals(const vector<Instruction>& inst)
{
	int sum = 0;
	int X = 1, cycles = 0;

	for (auto& op : inst)
	{
		int requiredCycles = (int)op.type + 1;
		if (op.type == InstructionType::NoOp)
		{
			cycles++;
			if ((cycles + 20) % 40 == 0) { sum += X * cycles; }
		}
		else
		{
			cycles++;
			if ((cycles + 20) % 40 == 0) { sum += X * cycles; }
			cycles++;
			if ((cycles + 20) % 40 == 0) { sum += X * cycles; }
			X += op.value;
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
		auto result = countSignals(inputs);
		cout << "Result: " << result << "\n";
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return RUN_ALL_TESTS();
}