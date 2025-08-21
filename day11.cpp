#include "aoc.hpp"

int count_digits(size_t n)
{
	int count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return count;
}

bool has_even_digits(size_t n)
{
	return (count_digits(n) % 2) == 0;
}

void split_number(size_t n, size_t *first, size_t *second)
{
	size_t digits = count_digits(n) / 2;
	size_t exp = 1L; // exp of 10
	LOG("Split " << n << " into ");
	while (digits--)
		exp *= 10L;
	*first = n / exp;
	*second = n % exp;
	LOG(*first << " and " << *second << "\n");
}

struct stone
{
	size_t value;
	stone *next;

	stone (size_t n) : value(n), next(NULL) {}

};

class stone_list
{
	private:
	stone *last;
	public:
	stone *first;

	stone_list() : first(NULL), last(NULL) {} 

	void add_stone(size_t n)
	{
		stone *s = new stone(n);
		if (first == NULL)
			first = last = s;
		else
		{
			last->next = s;
			last = last->next;
		}
	}

	size_t size()
	{
		size_t count = 0;
		stone *st = first;
		while (st)
		{
			st = st->next;
			count++;
		}
		return count;
	}

	void split(stone *st)
	{
		stone *new_stone = new stone(0);
		new_stone->next = st->next;
		st->next = new_stone;
		split_number(st->value, &st->value, &new_stone->value);
		if (last == st)
			last = st->next;
	}
};

void print_list(stone_list list)
{
	stone *st = list.first;
	LOG("list: ");
	while (st)
	{
		LOG(std::to_string(st->value) << ", ");
		st = st->next;
	}
	LOG("\n");
}

void part_one(stone_list list, int iteration)
{
	print_list(list);
	for (int i = 0; i < iteration; i++)
	{
		stone *st = list.first;
		while (st)
		{
			if (st->value == 0)
			{
				LOG("0 to 1\n");
				st->value = 1;
			}
			else if (has_even_digits(st->value))
			{
				list.split(st);
				st = st->next; // skip the splitted stone
			}
			else
			{
				LOG(st->value << " *= 2024\n");
				if (st->value > __LONG_MAX__ / 2024L)
					throw std::runtime_error("OVERFLOW");
				st->value *= 2024L;
			}
			st = st->next;
		}
		print_list(list);
	}
	std::cout << "Part one: "  << list.size() << std::endl;
}

void part_two(stone_list list, int iteration)
{
	int result = 0;
	std::cout << "Part two: " << result << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    string line;
	stone_list list;
    while (std::getline(file, line)) {
		std::istringstream stream(line);
		size_t n;
		while(stream >> n)
		{
			list.add_stone(n);
		}
    }
	part_one(list, 25);
	part_two(list, 75);
}