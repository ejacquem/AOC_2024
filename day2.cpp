#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

bool is_safe(std::vector<int> vec)
{
	int prev = vec[0];
	for (int i = 1; i < vec.size(); ++i)
	{
		int diff = abs(prev - vec[i]);
		if (vec[0] < vec[1] != prev < vec[i] || (diff < 1 || diff > 3))
			return false;	
		prev = vec[i];
	}
	return true;	
}

bool is_safe2(std::vector<int> vec)
{
	int prev = vec[0];
	for (int i = 1; i < vec.size(); ++i)
	{
		int diff = abs(prev - vec[i]);
		if (vec[0] < vec[1] != prev < vec[i] || (diff < 1 || diff > 3))
		{
			std::vector<int> vec1 = vec;
			vec1.erase(vec1.begin() + i - 1);

			std::vector<int> vec2 = vec;
			vec2.erase(vec2.begin() + i);
			return is_safe(vec1) || is_safe(vec2);	
		}
		prev = vec[i];
	}
	return true;	
}

void part_one(std::vector<std::vector<int>> array)
{
	int result = 0;
	for (std::vector<int> vec: array)
		result += is_safe(vec);
	std::cout << "Part one: "  << result << std::endl;
}

void part_two(std::vector<std::vector<int>> array)
{
	int result = 0;
	for (std::vector<int> vec: array)
		result += is_safe2(vec);
	std::cout << "Part two: " << result << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
	std::vector<std::vector<int>> array;
    while (std::getline(file, line)) {
        // std::cout << line << "\n";
		std::vector<int> row;
		std::istringstream stream = std::istringstream(line);
		int n = 0;
		while (stream >> n)
    		row.push_back(n);
		array.push_back(row);
	}
	part_one(array);
	part_two(array);
}