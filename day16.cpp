#include "aoc.hpp"
#include "pos.hpp"

struct cell 
{
	char symbol;
	bool valid;
	int score;

	cell(char v) : symbol(v), valid(false), score(0) {}
};

void traverse_map(vector<vector<cell>> &map, pos p, pos dir, int score);

void move(vector<vector<cell>> &map, pos p, pos current_dir, pos dir, int score)
{
	bool turning = (current_dir != dir);
	if (dir == current_dir * -1) // prevent going backward
		return;
	traverse_map(map, p + dir, dir, score + 1 + (turning ? 1000 : 0));
}

void print_map(vector<vector<cell>> &map)
{
	printf("map: \n");
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j].symbol == '#')
				printf(" #####");
			else
				printf(" %5d", map[i][j].score);
		}
		printf("\n");
	}
}

void print_map2(vector<vector<cell>> &map)
{
	printf("map: \n");
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j].symbol == '#')
				printf("# ");
			else
				printf("%c ", map[i][j].valid ? 'O' : '.');
		}
		printf("\n");
	}
}

void traverse_map(vector<vector<cell>> &map, pos p, pos dir, int score)
{
	cell &c = map[p.y][p.x];

	if (c.symbol == '#') // return if hit wall
		return;
	
	if (c.score && score >= c.score) // return if case has already a small score
		return;

	c.score = score;
	// print_map(map);

	if (c.symbol == 'E')
		return;
	move(map, p, dir, RIGHT, score);
	move(map, p, dir, LEFT, score);
	move(map, p, dir, UP, score);
	move(map, p, dir, DOWN, score);
}

int get_score(vector<vector<cell>> &map)
{
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j].symbol == 'E')
				return map[i][j].score;
		}
	}
	return -1;
}

int count_valid(vector<vector<cell>> &map)
{
	int count = 0;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j].valid)
				count++;
		}
	}
	return count;
}

pos get_start(vector<vector<cell>> &map)
{
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j].symbol == 'S')
				return {j, i};
		}
	}
	return {0, 0};
}

void part_one(vector<vector<cell>> &map)
{
	pos start = get_start(map);
	traverse_map(map, start, RIGHT, 0);
	std::cout << "Part one: "  << get_score(map) << std::endl;
}

// void traverse_map2(vector<vector<cell>> &map, pos p, pos dir, int score);

// void move2(vector<vector<cell>> &map, pos p, pos current_dir, pos dir, int score)
// {
// 	bool turning = (current_dir != dir);
// 	if (dir == current_dir * -1) // prevent going backward
// 		return;
// 	traverse_map2(map, p + dir, dir, score + 1 + (turning ? 1000 : 0));
// }

// void traverse_map2(vector<vector<cell>> &map, pos p, pos dir, int score)
// {
// 	cell &c = map[p.y][p.x];

// 	if (c.symbol == '#') // return if hit wall
// 		return;
	
// 	if (score != c.score)
// 		return;

// 	c.valid = true;

// 	move2(map, p, dir, RIGHT, score);
// 	move2(map, p, dir, LEFT, score);
// 	move2(map, p, dir, UP, score);
// 	move2(map, p, dir, DOWN, score);
// }

void part_two(vector<vector<cell>> &map)
{
	pos start = get_start(map);
	// traverse_map2(map, start, RIGHT, 0);
	std::cout << "Part two: " << count_valid(map) << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    string line;
	vector<vector<cell>> map;
    while (std::getline(file, line)) {
		map.push_back(vector<cell>(line.begin(), line.end()));
    }
	part_one(map);
	// part_two(map);
	// print_map2(map);
}