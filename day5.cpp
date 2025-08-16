#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>

using std::vector;
using std::string;
using std::unordered_set;

// no need to sort it, the middle element will have half the length in link 
int getMiddleListNumber(unordered_set<int> rules[100], vector<int> &list)
{
	for (int j = 0; j < list.size(); ++j)
	{
		int current_number = list[j];
		unordered_set<int> set = rules[current_number];
		int count = 0;
		for (int k = 0; k < list.size(); ++k)
		{
			if (k == j)
				continue;
			bool isLink = set.find(list[k]) != set.end();
			count += isLink;
		}
		if (count == list.size()/2)
			return current_number;
		// std::cout << std::endl;
	}
	std::cout << "Could not find the number" << std::endl;
	return 0;
}

bool isListValid(unordered_set<int> rules[100], vector<int> &list)
{
	for (int j = 0; j < list.size(); ++j)
	{
		int current_number = list[j];
		unordered_set<int> set = rules[current_number];
		for (int k = 0; k < list.size(); ++k)
		{
			if (k == j)
				continue;
			bool isLink = set.find(list[k]) != set.end();
			// std::cout << current_number << (isLink ? " is" : " is not") << " linked to " << list[k] << std::endl;
			if (k < j && isLink) // check if element before IS NOT in the set
				return false;
			if (k > j && !isLink) // check if element after IS in the set
				return false;
		}
		// std::cout << std::endl;
	}
	return true;
}

void part_one(unordered_set<int> rules[100], vector<vector<int>> pages)
{
	int result = 0;
	for (int i = 0; i < pages.size(); ++i)
	{
		// std::cout << "----- Parsing list " << i << " -----" << std::endl; 
		vector<int> list = pages[i];
		if (isListValid(rules, list))
		{
			result += list[list.size() / 2];
			std::cout << "List " << i << " Valid" << std::endl;
		}
		else
			std::cout << "List " << i << " Not Valid" << std::endl;
	}
	std::cout << "Part one: "  << result << std::endl;
}

void part_two(unordered_set<int> rules[100], vector<vector<int>> pages)
{
	int result = 0;
	for (int i = 0; i < pages.size(); ++i)
	{
		// std::cout << "----- Parsing list " << i << " -----" << std::endl; 
		vector<int> list = pages[i];
		if (!isListValid(rules, list))
			result += getMiddleListNumber(rules, list);
	}
	std::cout << "Part two: " << result << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
	unordered_set<int> rules[100];
	vector<vector<int>> pages;
    while (std::getline(file, line)) {
        // std::cout << line << "\n";
		if (line.length() < 3)
			continue;
		if (line.length() == 5 && line.at(2) == '|')
		{
			int first = std::stoi(string(line.begin(), line.begin() + 2));
			int secon = std::stoi(string(line.begin() + 3, line.begin() + 5));
			rules[first].emplace(secon); 
		}
		else
		{
			std::istringstream stream = std::istringstream(line);
			vector<int> vec;
			int n;
			std::cout << "parsing line: " << line << std::endl;
			char comma;
			while (stream >> n)
			{
				std::cout << n << ", " << std::endl;
				stream >> comma;
				vec.push_back(n);
			}
			pages.push_back(vec);
		}
    }
	part_one(rules, pages);
	part_two(rules, pages);
}