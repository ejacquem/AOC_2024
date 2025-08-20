#include "aoc.hpp"

void print_disk_map(vector<int> disk_map)
{
	for (int i: disk_map)
	{
		LOG(i);
	}
	LOG("\n");
}

void print_file_disk(vector<int> disk_map)
{
	for (int i: disk_map)
	{
		char c = (i == -1 ? '.' : ((i % 10) + '0'));
		LOG(c);
	}
	LOG("\n");
}

vector<int> get_file_disk(vector<int> &disk_map)
{
	vector<int> file_disk;
	for (int i = 0; i < disk_map.size(); i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < disk_map[i]; j++)
				file_disk.push_back(i/2);
		}
		else
		{
			for (int j = 0; j < disk_map[i]; j++)
				file_disk.push_back(-1);
		}
	}
	return file_disk;
}

long sum_file_disk(vector<int> &file_disk)
{
	long result = 0;
	for (int i = 0; i < file_disk.size(); i++)
	{
		if (file_disk[i] != -1)
		{
			result += file_disk[i] * i;
			LOG(file_disk[i] << " * " << i << " = " << file_disk[i] * i << "\n");
		}
	}
	return result;
}

void part_one(vector<int> disk_map)
{
	long result = 0;
	vector<int> file_disk = get_file_disk(disk_map);
	print_disk_map(disk_map);
	print_file_disk(file_disk);
	int start = 0;
	int end = file_disk.size() - 1;
	while (start < end)
	{
		if (file_disk[start] == -1)
		{
			while (file_disk[end] == -1 && start < end)
				end--;
			file_disk[start] = file_disk[end];
			file_disk[end] = -1;
		}
		start++;
	}
	print_file_disk(file_disk);
	result = sum_file_disk(file_disk);
	std::cout << "Part one: "  << result << std::endl;
}

int get_file_size(vector<int> file_disk, int end)
{
	int count = 0;
	int data = file_disk[end - count];
	while((end - count >= 0) && file_disk[end - count] == data)
		count++;
	LOG("file size of: " << file_disk[end] << ": " << count << "\n");
	return count;
}

int get_empty_space_size(vector<int> &file_disk, int start)
{
	int count = 0;
	while(start + count < file_disk.size() && file_disk[start + count] == -1)
		count++;
	return count;
}

void move_file(vector<int> &file_disk, int start, int end, int length)
{
	for (int i = 0; i < length; i++)
	{
		file_disk[start + i] = file_disk[end - i];
		file_disk[end - i] = -1;
	}	
}

void part_two(vector<int> disk_map)
{
	long result = 0;
	vector<int> file_disk = get_file_disk(disk_map);
	print_disk_map(disk_map);
	print_file_disk(file_disk);
	int end = file_disk.size() - 1;
	while (end > 0)
	{
		int start = 0;
		while (file_disk[end] == -1)
			end--;
		int file_size = get_file_size(file_disk, end);
		while(start < end)
		{
			while (file_disk[start] != -1)
				start++;
			if (start >= end)
				break;
			int empty_space = get_empty_space_size(file_disk, start);
			// LOG("Empty space: " << empty_space << "\n");
			if (empty_space >= file_size)
			{
				move_file(file_disk, start, end, file_size);
				// print_file_disk(file_disk);
				break;
			}
			start += empty_space;
		}
		end -= file_size;
	}
	print_file_disk(file_disk);
	result = sum_file_disk(file_disk);
	std::cout << "Part two: " << result << std::endl;
}

int main() {
    std::ifstream file("input.txt");
    string line;
	vector<int> disk_map;
    while (std::getline(file, line)) {
		for (char c: line)
			disk_map.push_back(c - '0');
		break;
    }
	part_one(disk_map);
	part_two(disk_map);
}