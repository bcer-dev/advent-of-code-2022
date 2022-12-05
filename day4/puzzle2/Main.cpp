#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
using namespace std;

struct SectionRange
{
	const int lower;
	const int upper;
	SectionRange(int lower, int upper);
};

SectionRange::SectionRange(int lower, int upper) : upper {upper}, lower {lower} {}

using SectionRangePair = pair<SectionRange, SectionRange>;

SectionRange parseSectionRange(const string& raw)
{
	auto hyphen = raw.find('-');
	auto lower = raw.substr(0, hyphen);
	auto upper = raw.substr(hyphen + 1);
	return SectionRange(stoi(lower), stoi(upper));
}

vector<SectionRangePair> loadInputs(const string& path)
{
	ifstream inputFile(path);
	if (!inputFile.is_open())
		throw runtime_error("Failed to open input file.");

	vector<SectionRangePair> inputs;

	string line;
	while (getline(inputFile, line))
	{
		auto comma = line.find(',');
		auto range1 = line.substr(0, comma);
		auto range2 = line.substr(comma + 1);
		inputs.push_back({parseSectionRange(range1), parseSectionRange(range2)});
	}

	inputFile.close();
	return inputs;
}

bool rangesOverlap(const SectionRangePair& ranges)
{
	auto& r1 = ranges.first;
	auto& r2 = ranges.second;

	if (r1.lower >= r2.lower && r1.upper <= r2.upper)
		return true;

	if (r2.lower >= r1.lower && r2.upper <= r1.upper)
		return true;	

	return false;
}

bool rangesOverlapAtAll(const SectionRangePair& ranges)
{
	auto& r1 = ranges.first;
	auto& r2 = ranges.second;

	for (int i = r1.lower; i <= r1.upper; i++)
	{
		SectionRange tmp(i, i);
		if (rangesOverlap({tmp, r2}))
			return true;
	}

	for (int i = r2.lower; i <= r2.upper; i++)
	{
		SectionRange tmp(i, i);
		if (rangesOverlap({tmp, r1}))
			return true;
	}

	return false;
}

TEST(SectionTests, HandlesSample1)
{
	SectionRange r1 {5, 7};
	SectionRange r2 {7, 9};
	EXPECT_EQ(rangesOverlapAtAll({r1, r2}), true);
}

TEST(SectionTests, HandlesSample2)
{
	SectionRange r1 {2, 8};
	SectionRange r2 {3, 7};
	EXPECT_EQ(rangesOverlapAtAll({r1, r2}), true);
}

TEST(SectionTests, HandlesSample3)
{
	SectionRange r1 {2, 4};
	SectionRange r2 {6, 8};
	EXPECT_EQ(rangesOverlapAtAll({r1, r2}), false);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	try
	{
		int overlaps = 0;
		for (auto& ranges : loadInputs("input/inputs.txt"))
		{
			if (rangesOverlapAtAll(ranges))
				overlaps++;
		}

		cout << "Total Overlaps: " << overlaps << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return RUN_ALL_TESTS();
}
