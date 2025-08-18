#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

#if DEBUG
 #define LOG(x) do { std::cout << x; } while(0)
#else
 #define LOG(x) 
#endif

using std::vector;

struct equation
{
	long result;
	vector<long> numbers;
};

bool bit_at(int number, int index)
{
	return (number >> index) & 1;
}

int trit_at(int number, int index)
{
    while (index-- > 0)
        number /= 3;

    return number % 3;
}

bool test_equation(equation eq, int patern)
{
	long result = 0;
	LOG( "Patern " << patern << ": " << eq.numbers[0]);
	for (int i = 0; i < eq.numbers.size(); i++)
	{
		if (i == 0)
			result = eq.numbers[0];
		else
		{
			if (bit_at(patern, i - 1)) {
				LOG( " + " << eq.numbers[i]);
				result += eq.numbers[i];
			}
			else {
				LOG( " * " << eq.numbers[i]);
				result *= eq.numbers[i];
			}
		}
		if (result > eq.result)
			break;
	}
	LOG( " = " << result << " | " << (result == eq.result ? "Yes!": "No!") << std::endl);
	return result == eq.result;
}

//same as above but with concatenation
bool test_equation_concatenation(equation eq, int patern)
{
	long result = 0;
	LOG( "Patern " << patern << ": " << eq.numbers[0]);
	for (int i = 0; i < eq.numbers.size(); i++)
	{
		if (i == 0)
			result = eq.numbers[0];
		else
		{
			int trit = trit_at(patern, i - 1);
			if (trit == 0) {
				LOG( " + " << eq.numbers[i]);
				result += eq.numbers[i];
			}
			else if (trit == 1) {
				LOG( " * " << eq.numbers[i]);
				result *= eq.numbers[i];
			}
			else if (trit == 2) {
				LOG( " || " << eq.numbers[i]);
				std::string number = std::to_string(result) + std::to_string(eq.numbers[i]);
				result = std::stol(number);
			}
		}
		if (result > eq.result)
			break;
	}
	LOG( " = " << result << " | " << (result == eq.result ? "Yes!": "No!") << std::endl);
	return result == eq.result;
}

void part_one(vector<equation> input)
{
	long result = 0;
	for (equation eq: input)
	{
		long operator_number = pow(2, eq.numbers.size() - 1); // possibility of operators
		LOG( "testing equation with 2^" << eq.numbers.size() - 1 << " | " << operator_number << " operators" << std::endl);
		for (int i = 0; i < operator_number; i++)
		{
			if (test_equation(eq, i))
			{
				result += eq.result;
				break;
			}
		}
	}
	std::cout << "Part one: "  << result << std::endl;
}

void part_two(vector<equation> input)
{
	long result = 0;
	for (equation eq: input)
	{
		long operator_number = pow(3, eq.numbers.size() - 1); // possibility of operators
		LOG( "testing equation with 3^" << eq.numbers.size() - 1 << " | " << operator_number << " operators" << std::endl);
		for (int i = 0; i < operator_number; i++)
		{
			if (test_equation_concatenation(eq, i))
			{
				result += eq.result;
				break;
			}
		}
	}
	std::cout << "Part two: " << result << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
	vector<equation> input;
    while (std::getline(file, line)) {
        // std::cout << line << "\n";
		std::istringstream stream(line);
		equation eq;
		long number;
		char dotdot;
		stream >> eq.result >> dotdot;
		LOG(eq.result << dotdot << " ");
		while (stream >> number){
			eq.numbers.push_back(number);
			LOG(number << " ");
		}
		LOG(std::endl);
		input.push_back(eq);
    }
	part_one(input);
	part_two(input);
}