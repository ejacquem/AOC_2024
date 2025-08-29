#include "aoc.hpp"
#include "pos.hpp"
#include <regex>
#include <string>
#include <iostream>
#include <math.h>

struct robot
{
	pos p;
	pos vel;
};

void print_robot(robot r)
{
	LOG("Robot: " << r.p << ", " << r.vel << "\n");
}

void add_robot(int *quadrants, int index, pos r)
{
	// LOG("Quadrants " << index << ": adding " << r << "\n");
	quadrants[index] += 1;
}

void part_one(vector<robot> &robots)
{
	int result = 0;
	int quadrants[4] = {0};
	const int iter = 100;
	const int w = 101, h = 103;
	for (robot r : robots)
	{
		pos final = r.p + r.vel * iter;
		final.x = (final.x % w + w) % w;
		final.y = (final.y % h + h) % h;
		if (final.x < w / 2 && final.y < h / 2)
			add_robot(quadrants, 0, final);
		if (final.x > w / 2 && final.y < h / 2)
			add_robot(quadrants, 1, final);
		if (final.x < w / 2 && final.y > h / 2)
			add_robot(quadrants, 2, final);
		if (final.x > w / 2 && final.y > h / 2)
			add_robot(quadrants, 3, final);
	}
	result = quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3];
	LOG("Quadrants 0 = " << quadrants[0] << std::endl);
	LOG("Quadrants 1 = " << quadrants[1] << std::endl);
	LOG("Quadrants 2 = " << quadrants[2] << std::endl);
	LOG("Quadrants 3 = " << quadrants[3] << std::endl);
	std::cout << "Part one: "  << result << std::endl;
}

void print_map(vector<robot> &robots, int iter)
{
	const int w = 101, h = 103;
	char map[h][w] = {0};
	LOG("Printing map at index: " << iter << std::endl);
	for (robot r : robots)
	{
		pos final = r.p + r.vel * iter;
		final.x = (final.x % w + w) % w;
		final.y = (final.y % h + h) % h;
		map[final.y][final.x]++; 
	}
	for (int i = 0; i < w + 3; i++)
		LOG("-");
	LOG(std::endl);
	for (int i = 0; i < h; i++)
	{
		LOG("|");
		if (i == h/2)
		{
			for (int k = 0; k <= w; k++)
			{
				if (k == w/2)
					LOG("+");
				else 
					LOG("-");
			}
			LOG("|");
			LOG(std::endl);
			LOG("|");
		}
		for (int j = 0; j < w; j++)
		{
			if (j == w/2)
				LOG("|");
			LOG((map[i][j] == 0 ? ' ' : 'x'));
		}
		LOG("|");
		LOG(std::endl);
	}
	for (int i = 0; i < w + 3; i++)
		LOG("-");
	LOG(std::endl);
}

void part_two(vector<robot> &robots)
{
	int result = 0;
	const int max_iter = 10000;
	const int w = 101, h = 103;
	for (int i = 0; i < max_iter; i++)
	{
		int quadrants[4] = {0};
		for (robot r : robots)
		{
			pos final = r.p + r.vel * i;
			final.x = (final.x % w + w) % w;
			final.y = (final.y % h + h) % h;
			if (final.x < w / 2 && final.y < h / 2)
				add_robot(quadrants, 0, final);
			if (final.x > w / 2 && final.y < h / 2)
				add_robot(quadrants, 1, final);
			if (final.x < w / 2 && final.y > h / 2)
				add_robot(quadrants, 2, final);
			if (final.x > w / 2 && final.y > h / 2)
				add_robot(quadrants, 3, final);
		}
		for (int j = 0; j < 4; j++)
		{
			if (quadrants[j] > 200)
			{
				result = i;
				LOG("Quadrants " << j << " has " << quadrants[j] << " robots in it, kinda sus\n");
				print_map(robots, i);
			}
		}
		if (result) break;
	}
	std::cout << "Part two: " << result << std::endl;
}

robot parse_robot(string &line)
{
	robot r;
	int scanned = sscanf(line.c_str(), "p=%d,%d v=%d,%d", &r.p.x, &r.p.y, &r.vel.x, &r.vel.y);
	if (scanned != 4)
		throw std::runtime_error("Parse Error");
	return r;
}

int main() {
    std::ifstream file("input.txt");
    string line;
	vector<robot> robots;
    while (std::getline(file, line)) {
        // std::cout << line << "\n";
		robot r = parse_robot(line);
		print_robot(r);
		robots.push_back(r);
    }
	part_one(robots);
	part_two(robots);
	LOG("Robots: " << robots.size() << std::endl);
}