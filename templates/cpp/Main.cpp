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
	inputFile.close();
	return inputs;
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
