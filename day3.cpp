#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <regex>

using std::string;
using std::vector;
using std::regex;

// parse string of format mul(n, n)
long parse_mul(string str)
{
	long result = 1;
    std::regex number_patern("\\d+");

    auto begin = std::sregex_iterator(str.begin(), str.end(), number_patern);
    auto end   = std::sregex_iterator();
	
    for (auto it = begin; it != end; ++it) {
        // std::cout << it->str() << "\n";
		result*= std::stol(it->str());
    }
	return result;
}

void part_one(string input)
{
	int result = 0;
	
    std::regex mul_patern("mul\\(\\d+\\,\\d+\\)");
    std::regex number_patern("\\d+");
	
    auto begin = std::sregex_iterator(input.begin(), input.end(), mul_patern);
    auto end   = std::sregex_iterator();
	
    for (auto it = begin; it != end; ++it) {
		// std::cout << it->str() << " at position: " << it->position() << "\n";
		result += parse_mul(it->str());
    }
	std::cout << "Part one: "  << result << std::endl;
}

void part_two(string input)
{
	int result = 0;
	
    std::regex mul_patern("(mul\\(\\d+\\,\\d+\\))|(don't\\(\\))|(do\\(\\))");
    std::regex number_patern("\\d+");
	
    auto begin = std::sregex_iterator(input.begin(), input.end(), mul_patern);
    auto end   = std::sregex_iterator();
	
	bool enable = true;
    for (auto it = begin; it != end; ++it) {
		// std::cout << it->str() << " at position: " << it->position() << "\n";
		if (it->str() == "don't()")
			enable = false;
		else if (it->str() == "do()")
			enable = true;
		else if (enable)
			result += parse_mul(it->str());
    }
	std::cout << "Part two: " << result << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    string line;
	string input;
    while (std::getline(file, line)) {
        // std::cout << line << "\n";
		input += line;	
    }
	part_one(input);
	part_two(input);
}