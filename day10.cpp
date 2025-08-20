#include "aoc.hpp"
#include "pos.hpp"

void print_map(vector<vector<char>> &map)
{
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			LOG(map[i][j]);
		}
		LOG(std::endl);
	}
}

char get_value(vector<vector<char>> &map, pos p)
{
	if (p.y >= 0 && p.x >= 0 && p.y < map.size() && p.x < map[p.y].size())
        return map[p.y][p.x];
    return -1;
}

void naviguate_map(vector<vector<char>> &map, pos p, std::unordered_set<pos, pos_hash> &set)
{
    char current = get_value(map, p);
    LOG(current << " ");
    if (current == -1)
        return;
    if (current == '9')
    {
        LOG(" Found 9!\n");
        set.emplace(p);
        return;
    }
    if (get_value(map, p + UP) == current + 1)
    {
        LOG("Going Up\n");
        naviguate_map(map, p + UP, set);
    }
    if (get_value(map, p + DOWN) == current + 1)
    {
        LOG("Going Down\n");
        naviguate_map(map, p + DOWN, set);
    }
    if (get_value(map, p + LEFT) == current + 1)
    {
        LOG("Going Left\n");
        naviguate_map(map, p + LEFT, set);
    }
    if (get_value(map, p + RIGHT) == current + 1)
    {
        LOG("Going Right\n");
        naviguate_map(map, p + RIGHT, set);
    }
}

int naviguate_map2(vector<vector<char>> &map, pos p)
{
    char current = get_value(map, p);
    LOG(current << " ");
    if (current == -1)
        return 0;
    if (current == '9')
        return 1;
    int count = 0;
    if (get_value(map, p + UP) == current + 1)
        count += naviguate_map2(map, p + UP);
    if (get_value(map, p + DOWN) == current + 1)
        count += naviguate_map2(map, p + DOWN);
    if (get_value(map, p + LEFT) == current + 1)
        count += naviguate_map2(map, p + LEFT);
    if (get_value(map, p + RIGHT) == current + 1)
        count += naviguate_map2(map, p + RIGHT);
    return count;
}

void part_one(vector<vector<char>> map)
{
    int result = 0;
    print_map(map);
    std::unordered_set<pos, pos_hash> set;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            pos p = (pos){j, i};
            if (get_value(map, p) == '0')
            {
                naviguate_map(map, p, set);
                int trail_head = set.size();
                result += trail_head;
                LOG("Found " << trail_head << " trail_head starting at: " << p << "\n");
                set.clear();
            }
        }
    }
    std::cout << "Part one: " << result << std::endl;
}

void part_two(vector<vector<char>> map)
{
    int result = 0;
    print_map(map);
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            pos p = (pos){j, i};
            if (get_value(map, p) == '0')
            {
                int trail_head = naviguate_map2(map, p);
                result += trail_head;
                LOG("Found " << trail_head << " trail_head starting at: " << p << "\n");
            }
        }
    }
    std::cout << "Part two: " << result << std::endl;
}

int main()
{
    std::ifstream file("input.txt");
    string line;
    vector<vector<char>> map;
    while (std::getline(file, line))
    {
        // std::cout << line << "\n";
        map.push_back(vector<char>(line.begin(), line.end()));
    }
    part_one(map);
    part_two(map);
}