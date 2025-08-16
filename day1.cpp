#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

void part_one(std::vector<int> a, std::vector<int> b)
{
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());
	int result = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		result += abs(a[i] - b[i]);
	}
	std::cout << "Part one: "  << result << std::endl;
}

void part_two(std::vector<int> a, std::vector<int> b)
{
	int result = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		int count = 0; 
		for (int j = 0; j < a.size(); ++j)
		{
			if (a[i] == b[j])
				++count;
		}
		result += a[i] * count;
	}
	std::cout << "Part two: " << result << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
	std::vector<int> a;
	std::vector<int> b;
    while (std::getline(file, line)) {
        // std::cout << line << "\n";
		int n, m;
		std::istringstream(line) >> n >> m;
		a.push_back(n);
		b.push_back(m);
    }
	part_one(a, b);
	part_two(a, b);
}