#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include "pos.hpp"

#if DEBUG
 #define LOG(x) do { std::cout << x; } while(0)
#else
 #define LOG(x) 
#endif

using std::vector;
using std::string;
using std::unordered_set;
using std::unordered_map;

struct cell
{
	char value;
	bool is_antinodes;

	cell(char v) : value(v), is_antinodes(false) {}
};

void print_map(vector<vector<cell>> &map)
{
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			LOG(map[i][j].value);
		}
		LOG(std::endl);
	}
}

void print_map_antinodes(vector<vector<cell>> &map)
{
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			LOG((map[i][j].is_antinodes ? "#" : "."));
		}
		LOG(std::endl);
	}
}

unordered_map<char, vector<pos>> get_antenas(vector<vector<cell>> &map)
{
	unordered_map<char, vector<pos>> antenas;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			cell c = map[i][j];
			if (c.value != '.')
			{
				antenas[c.value].push_back((pos){j, i});
				LOG("Found antenas " << c.value << " at " << i << ", " << j << "\n");
			}
		}
	}
	return antenas;
}

//return true if set successfully
bool set_antinodes(vector<vector<cell>> &map, pos p)
{
	if (p.y >= 0 && p.x >= 0 && p.y < map.size() && p.x < map[p.y].size()) {
		map[p.y][p.x].is_antinodes = true;
		return true;
	}
	return false;
}

void map_antinodes(vector<vector<cell>> &map, vector<pos> &pos_list)
{
	for (int i = 0; i < pos_list.size(); i++)
	{
		for (int j = i + 1; j < pos_list.size(); j++)
		{
			pos a = pos_list[i];
			pos b = pos_list[j];
			pos antinode1 = a + ((b - a) * 2);
			pos antinode2 = b + ((a - b) * 2);
			set_antinodes(map, antinode1);
			set_antinodes(map, antinode2);
			LOG("A: (" << a.x << ", " << a.y << ") | B (" << b.x << ", " << b.y << 
				") \n antinodes: (" << antinode1.x << ", " << antinode1.y << 
				") | (" << antinode2.x << ", " << antinode2.y << ")\n");
		}
	}
}

void map_antinodes2(vector<vector<cell>> &map, vector<pos> &pos_list)
{
	for (int i = 0; i < pos_list.size(); i++)
	{
		for (int j = i + 1; j < pos_list.size(); j++)
		{
			pos a = pos_list[i];
			pos b = pos_list[j];
			pos atob = (b - a);
			pos btoa = (a - b);
			while (set_antinodes(map, a))
				a+=atob;
			while (set_antinodes(map, b))
				b+=btoa;
		}
	}
}

int count_antinodes(vector<vector<cell>> &map)
{
	int result = 0;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			cell c = map[i][j];
			if (c.is_antinodes)
				result++;
		}
	}
	return result;
}

void part_one(vector<vector<cell>> map)
{
	int result = 0;
	LOG("before:\n");
	print_map(map);
	print_map_antinodes(map);
	unordered_map<char, vector<pos>> antenas = get_antenas(map);
	for (auto &[key, positions] : antenas) {
		map_antinodes(map, positions);
	}
	result = count_antinodes(map);
	LOG("after:\n");
	print_map(map);
	print_map_antinodes(map);
	std::cout << "Part one: "  << result << std::endl;
}

void part_two(vector<vector<cell>> map)
{
	int result = 0;
	LOG("before:\n");
	print_map(map);
	print_map_antinodes(map);
	unordered_map<char, vector<pos>> antenas = get_antenas(map);
	for (auto &[key, positions] : antenas) {
		map_antinodes2(map, positions);
	}
	result = count_antinodes(map);
	LOG("after:\n");
	print_map(map);
	print_map_antinodes(map);
	std::cout << "Part two: " << result << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    string line;
	vector<vector<cell>> map;
    while (std::getline(file, line)) {
        // std::cout << line << "\n";
		map.push_back(vector<cell>(line.begin(), line.end()));
    }
	part_one(map);
	part_two(map);
}