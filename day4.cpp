#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <regex>

using std::string;
using std::vector;

int find_xmas(string str)
{
    std::regex patern_xmas("XMAS");
    std::regex patern_samx("SAMX");

    auto begin_xmas = std::sregex_iterator(str.begin(), str.end(), patern_xmas);
    auto end_xmas = std::sregex_iterator();
    auto begin_samx = std::sregex_iterator(str.begin(), str.end(), patern_samx);
    auto end_samx = std::sregex_iterator();

    int count = std::distance(begin_xmas, end_xmas) + std::distance(begin_samx, end_samx);

    // std::cout << "Found " << count << " matches." << std::endl;
	return count;
}

string diagonal2_parse(vector<string> input)
{
	string str;

	const int height = input.size();
	const int width = input[0].length();
	for (int i = 0; i < height + width; ++i)
	{
		int x = width, y = height + width - i	;
		for (;y >= 0 || x >= 0; --x, --y)
		{
			if (y < height && x < width && y >= 0 && x >= 0)
				str += input[y][x];
		}
		str += '|';
	}
	// std::cout << str << std::endl;
	return str;
}

string diagonal_parse(vector<string> input)
{
	string str;

	const int height = input.size();
	const int width = input[0].length();
	for (int i = 0; i < height + width; ++i)
	{
		int x = 0, y = i;
		for (;y >= 0 || x < height + width; ++x, --y)
		{
			if (y < height && x < width && y >= 0 && x >= 0)
				str += input[y][x];
		}
		str += '|';
	}
	// std::cout << str << std::endl;
	return str;
}

string vertical_parse(vector<string> input)
{
	string str;
	for (int j = 0; j < input[0].length(); ++j)
	{
		for (int i = 0; i < input.size(); ++i)
		{
			str += input[i][j];
		}
		str += '|';
	}
	return str;
}

string horizontal_parse(vector<string> input)
{
	string str;
	for (int i = 0; i < input.size(); ++i)
	{
		str += input[i] + '|';
	}
	return str;
}

void part_one(vector<string> input)
{
	int result = 0;

	int h, v, d, d2;
	h = find_xmas(horizontal_parse(input));
	v = find_xmas(vertical_parse(input));
	d = find_xmas(diagonal_parse(input));
	d2 = find_xmas(diagonal2_parse(input));
	std::cout << "Horizontal: " << h << std::endl;
	std::cout << "Vertical: " << v << std::endl;
	std::cout << "Diagonal: " << d << std::endl;
	std::cout << "Diagonal2: " << d2 << std::endl;
	std::cout << "Part one: "  << h + v + d + d2 << std::endl;
}

bool is_sm_or_ms(char a, char b)
{
	return (a == 'S' && b == 'M') || (a == 'M' && b == 'S');
}

void part_two(vector<string> input)
{
	int result = 0;
	for (int i = 1; i < input.size() - 1; i++)
	{
		for (int j = 1; j < input[0].length() - 1; j++)
		{
			char tl, tr, c, bl, br; // top left, top right, center, bot left, bot right
			tl = input[i-1][j-1];
			tr = input[i-1][j+1];
			c = input[i][j];
			bl = input[i+1][j-1];
			br = input[i+1][j+1];
			if (c == 'A' && is_sm_or_ms(tl, br) && is_sm_or_ms(tr, bl))
			result++;
		}
	}
	
	std::cout << "Part two: " << result << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
	vector<string> input;
    while (std::getline(file, line)) {
        // std::cout << line << "\n";
		input.push_back(line);
    }
	part_one(input);
	part_two(input);
}