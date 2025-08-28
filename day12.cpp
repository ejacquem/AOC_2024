#include "aoc.hpp"
#include "pos.hpp"

struct cell 
{
	char symbol;
	bool visited;

	cell(char v) : symbol(v), visited(false) {}
};

struct region
{
	char symbol;
	size_t area;
	size_t perimeter;
	size_t corner;
	size_t price() {return area * perimeter;}
	size_t price_discount() {return area * corner;}
};

bool in_bound(vector<vector<cell>> &map, pos p)
{
	return (p.y >= 0 && p.x >= 0 && p.y < map.size() && p.x < map[p.y].size());
}

void fill_region(vector<vector<cell>> &map, pos p, region &r)
{
	if (in_bound(map, p) && map[p.y][p.x].symbol == r.symbol)
	{
		if (map[p.y][p.x].visited)
			return;
		r.area++;
		map[p.y][p.x].visited = true;
		fill_region(map, p + UP, r);
		fill_region(map, p + DOWN, r);
		fill_region(map, p + LEFT, r);
		fill_region(map, p + RIGHT, r);
	}
	else
		r.perimeter++;
}

// return true if the tile is from the region
bool fill_region2(vector<vector<cell>> &map, pos p, region &r)
{
	if (in_bound(map, p) && map[p.y][p.x].symbol == r.symbol)
	{
		if (map[p.y][p.x].visited)
			return true;
		r.area++;
		map[p.y][p.x].visited = true;
		bool up = fill_region2(map, p + UP, r);
		bool down = fill_region2(map, p + DOWN, r);
		bool left = fill_region2(map, p + LEFT, r);
		bool right = fill_region2(map, p + RIGHT, r);
		int corner = (!up && !left) + (!up && !right) + (!down && !left) + (!down && !right);
		//check inner corner
		if (up && left) {
			pos temp = p + UP + LEFT;
			corner += map[temp.y][temp.x].symbol != r.symbol;
		}
		if (up && right) {
			pos temp = p + UP + RIGHT;
			corner += map[temp.y][temp.x].symbol != r.symbol;
		}
		if (down && left) {
			pos temp = p + DOWN + LEFT;
			corner += map[temp.y][temp.x].symbol != r.symbol;
		}
		if (down && right) {
			pos temp = p + DOWN + RIGHT;
			corner += map[temp.y][temp.x].symbol != r.symbol;
		}
		r.corner += corner;
		// std::cout << "up: " << up << " down: " << down << " left: " << left << " right: " << right << " corner: " << corner << std::endl;
		return true;
	}
	else
		r.perimeter++;
	return false;
}

void print_region(region &r)
{
	printf("Region '%c': Area = %zu, Perimeter = %zu, Price = %zu\n", r.symbol, r.area, r.perimeter, r.price());
}

void print_region2(region &r)
{
	printf("Region '%c': Area = %zu, Corner = %zu, Price = %zu\n", r.symbol, r.area, r.corner, r.price_discount());
}

void part_one(vector<vector<cell>> map)
{
	size_t result = 0;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			cell c = map[i][j];
			region r = {0};
			r.symbol = c.symbol;
			if (c.visited == false)
			{
				// std::cout << c.symbol << std::endl;
				fill_region(map, (pos){j, i}, r);
				// print_region(r);
				result += r.price();
			}
		}
	}
	std::cout << "Part one: "  << result << std::endl;
}

void part_two(vector<vector<cell>> map)
{
	int result = 0;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			cell c = map[i][j];
			region r = {0};
			r.symbol = c.symbol;
			if (c.visited == false)
			{
				// std::cout << c.symbol << std::endl;
				fill_region2(map, (pos){j, i}, r);
				// print_region2(r);
				result += r.price_discount();
			}
		}
	}
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