#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#if DEBUG
 #define LOG(x) do { std::cout << x; } while(0)
#else
 #define LOG(x) 
#endif

using std::vector;
using std::string;

void part_one()
{
	int result = 0;
	std::cout << "Part one: "  << result << std::endl;
}

void part_two()
{
	int result = 0;
	std::cout << "Part two: " << result << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    string line;
    while (std::getline(file, line)) {
        // std::cout << line << "\n";
    }
	part_one();
	part_two();
}