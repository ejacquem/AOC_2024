#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <vector>

using std::vector;
using std::string;

bool is_obstacle(char c)
{
	return c == '#';
}

bool is_player(char c)
{
	return c == 'v' || c == '<' || c == '^' || c == '>';
}

struct pos
{
	int x;
	int y;
    pos operator+(const pos& other) const {
        return {x + other.x, y + other.y};
    }

    pos operator-(const pos& other) const {
        return {x - other.x, y - other.y};
    }

	pos& operator+=(const pos& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    pos& operator-=(const pos& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

	bool operator==(const pos& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const pos& other) const {
        return !(*this == other);
    }
};

#define UP		(pos){0, -1}
#define DOWN	(pos){0, 1}
#define LEFT	(pos){-1, 0}
#define RIGHT	(pos){1, 0}

pos get_player_pos(vector<vector<char>> &map)
{
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[j].size(); j++) {
			if (is_player(map[i][j]))
				return (pos){j, i};
		}
	}
	std::cout << "could not find player\n";
	exit(1);
	return (pos){0};
}

int countX(vector<vector<char>> &map)
{
	int count = 0;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[j].size(); j++) {
			if (map[i][j] == 'X')
				count++;
		}
	}
	return count;
}

bool in_bound(pos p, int h, int w)
{
	return p.x >= 0 && p.y >= 0 && p.x < w && p.y < h;
}

void print_map(vector<vector<char>> &map)
{
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[j].size(); j++) {
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}

void part_one(vector<vector<char>> map)
{
	int height = map.size();
	int width = map[0].size();
	pos player_pos = get_player_pos(map);
	pos direction = (pos){0, -1};
	// std::cout << "map before: \n";
	// print_map(map);
	while(in_bound(player_pos, height, width))
	{
		if (is_obstacle(map[player_pos.y][player_pos.x]))
		{
			player_pos -= direction;
			if (direction == UP) direction = RIGHT;
			else if (direction == RIGHT) direction = DOWN;
			else if (direction == DOWN) direction = LEFT;
			else if (direction == LEFT) direction = UP;
		}
		else
		{
			map[player_pos.y][player_pos.x] = 'X';
		}
		player_pos += direction;
	}
	// std::cout << "map after: \n";
	// print_map(map);
	std::cout << "Part one: "  << countX(map) << std::endl;
}

bool is_in_loop(vector<vector<char>> map)
{
	int height = map.size();
	int width = map[0].size();
	pos player_pos = get_player_pos(map);
	pos direction = UP;
	bool same_path_since_last_turn = false;
	int same_path_turn_count = 0; // count each turn if no new path has been cross
	int iteration = 0;
	while(in_bound(player_pos, height, width))
	{
		if (iteration == 1000000)
			std::cout << "too much iteration";
		iteration++;
		if (is_obstacle(map[player_pos.y][player_pos.x]))
		{
			if (same_path_since_last_turn)
				same_path_turn_count++;
			if (same_path_turn_count == 5) // keep this number growing if the result continues to change 4 was enough for the input
				return true;
			same_path_since_last_turn = true;
			player_pos -= direction;
			if		(direction == UP) direction = RIGHT;
			else if (direction == RIGHT) direction = DOWN;
			else if (direction == DOWN) direction = LEFT;
			else if (direction == LEFT) direction = UP;
		}
		else
		{
			if (map[player_pos.y][player_pos.x] != 'X')
				same_path_since_last_turn = false;
			map[player_pos.y][player_pos.x] = 'X';
		}
		player_pos += direction;
	}
	return false;
}

void part_two(vector<vector<char>> map)
{
	int result = 0;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[j].size(); j++) {
			if (map[i][j] == '.')
			{
				map[i][j] = '#';
				if (is_in_loop(map))
					result++;
				map[i][j] = '.';
			}
		}
	}
	std::cout << "Part two: " << result << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
	vector<vector<char>> map;
    while (std::getline(file, line)) {
        // std::cout << line << "\n";
		vector<char> row;
		for (char c: line)
		{
			row.push_back(c);
		}
		map.push_back(row);
    }
	part_one(map);
	part_two(map);
}