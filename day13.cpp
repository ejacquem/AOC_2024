#include "aoc.hpp"
#include "posl.hpp"
#include <regex>
#include <string>
#include <iostream>
#include <math.h>

using std::getline;
const float epsilon = 0.001;

struct clawmachine
{
	pos buttonA;
	pos buttonB;
	pos prize;
};

void print_claw_machine(clawmachine cm)
{
	LOG("ButtonA: " << cm.buttonA << ", ButtonB: " << cm.buttonB << ", Prize: " << cm.prize << std::endl);
}

bool is_close_to_int(double value, double epsilon = 0.001f) {
    return std::fabs(value - std::round(value)) < epsilon;
}

size_t solve(clawmachine cm)
{
	double Ax, Ay, Bx, By, Px, Py;
	Ax = cm.buttonA.x;
	Ay = cm.buttonA.y;
	Bx = cm.buttonB.x;
	By = cm.buttonB.y;
	Px = cm.prize.x;
	Py = cm.prize.y;
	double x = (Px / (Ax - ((Bx * Ay) / By))) - ((Bx * Py) / (Ax * By - Bx * Ay));
	double y = (Py - Ay * x) / By;
	LOG("X: " << x << ", Y: " << y);
	if (!is_close_to_int(x) || !is_close_to_int(y))
		return 0;
	size_t roundx = std::round(x);
	size_t roundy = std::round(y);
	return roundx * 3u + roundy;
}

void part_one(vector<clawmachine> machines)
{
	size_t result = 0;
	for (clawmachine m : machines)
	{
		size_t tokens = solve(m);
		LOG(" Tokens: " << tokens << std::endl);
		result += tokens;
	}
	std::cout << "Part one: "  << result << std::endl;
}

void part_two(vector<clawmachine> machines)
{
	size_t result = 0;
	for (clawmachine m : machines)
	{
		m.prize += {10000000000000, 10000000000000};
		size_t tokens = solve(m);
		LOG(" Tokens: " << tokens << std::endl);
		result += tokens;
	}
	std::cout << "Part two: " << result << std::endl;
}

void parse_button(pos *button, std::string str)
{
	std::regex re(R"(Button (\w+): X([+-]?\d+), Y([+-]?\d+))");
	std::smatch match;

	if (std::regex_match(str, match, re)) {
		std::string buttonLabel = match[1];
		int x = std::stoi(match[2]);
		int y = std::stoi(match[3]);
		// std::cout << buttonLabel << " " << x << " " << y << "\n";
		button->x = x;
		button->y = y;
	}
}

void parse_prize(pos *prize, const std::string &str)
{
    std::regex re(R"(Prize: X=(\d+), Y=(\d+))");
    std::smatch match;

    if (std::regex_match(str, match, re)) {
        prize->x = std::stoi(match[1]);
        prize->y = std::stoi(match[2]);
        // std::cout << "Prize: " << prize->x << ", " << prize->y << "\n";
    }
}

int main() {
    std::ifstream file("input.txt");
    string buttonA, buttonB, prize, nl;
	clawmachine cm;
	vector<clawmachine> machines;
	std::istringstream stream;
    while (getline(file, buttonA) && getline(file, buttonB) && getline(file, prize)) {
			parse_button(&cm.buttonA, buttonA);
			parse_button(&cm.buttonB, buttonB);
			parse_prize(&cm.prize, prize);
			print_claw_machine(cm);
			machines.push_back(cm);
			getline(file, nl); // skip new line
	}
	part_one(machines);
	part_two(machines);
}