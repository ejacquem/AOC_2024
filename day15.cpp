#include "aoc.hpp"
#include "pos.hpp"

void print_map(vector<vector<char>> &map)
{
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
            LOG((char)map[i][j]);
        LOG(std::endl);
    }
}

size_t count_gps_map(vector<vector<char>> &map)
{
    size_t result = 0;
    for (int i = 0; i < map.size(); i++)
        for (int j = 0; j < map[i].size(); j++)
            if (map[i][j] == 'O') result += 100 * i + j;
    return result;
}

pos get_dir(char move)
{
    if (move == '>')
        return RIGHT;
    if (move == '^')
        return UP;
    if (move == 'v')
        return DOWN;
    if (move == '<')
        return LEFT;
    LOG("Wrong move: " << (char)move);
    return LEFT;
}

void move_bot(vector<vector<char>> &map, pos dir, pos &p)
{
    map[p.y][p.x] = '.';
    p += dir;
    map[p.y][p.x] = '@';
}

pos get_bot_pos(vector<vector<char>> &map)
{
    for (int i = 0; i < map.size(); i++)
        for (int j = 0; j < map[i].size(); j++)
            if (map[i][j] == '@') return {j, i};
    LOG("Bot not found\n");
    return {0, 0};
}

void try_move_bot(vector<vector<char>> &map, char move, pos &p)
{
    pos dir = get_dir(move);

    pos new_pos = p + dir;
    if (map[new_pos.y][new_pos.x] == '.')
        move_bot(map, dir, p);
    else if (map[new_pos.y][new_pos.x] == 'O')
    {
        pos box = new_pos;
        while (map[box.y][box.x] == 'O')
            box += dir;
        if (map[box.y][box.x] == '.')
        {
            move_bot(map, dir, p);
            map[box.y][box.x] = 'O';
        }
    }
}

void part_one(vector<vector<char>> map, string moves)
{
    pos bot_pos = get_bot_pos(map);
    print_map(map);
    for (char move : moves)
    {
        LOG("Move: " << move << "\n");
        try_move_bot(map, move, bot_pos);
        print_map(map);
    }
    std::cout << "Part one: "  << count_gps_map(map) << std::endl;
}

// #define L(x) printf(x)
#define L(x) 1

#define IS_BOX(c) (c == '[' || c == ']')
#define IS_FREE(c) (c == '.')
#define BOTH_FREE(f1, f2) 				(IS_FREE(f1) && IS_FREE(f2) && L("BOTH_FREE\n"))
#define LEFT_FREE_AND_RIGHT_BOX(f1, f2) (IS_FREE(f1) && IS_BOX(f2) 	&& L("LEFT_FREE_AND_RIGHT_BOX\n"))
#define LEFT_BOX_AND_RIGHT_FREE(f1, f2) (IS_BOX(f1) && IS_FREE(f2) 	&& L("LEFT_BOX_AND_RIGHT_FREE\n"))
#define BOTH_ONE_BOX(f1, f2) 			(f1 == '[' && f2 == ']' 	&& L("BOTH_ONE_BOX\n"))
#define BOTH_TWO_BOX(f1, f2) 			(f1 == ']' && f2 == '[' 	&& L("BOTH_TWO_BOX\n"))
#include <cstring>

// return true if the box has been pushed
bool can_push_box_vertical(vector<vector<char>> &map, pos dir, pos p1, pos p2, bool apply)
{
    pos next_p1 = p1 + dir;
    pos next_p2 = p2 + dir;
    char f1 = map[next_p1.y][next_p1.x]; // front one
    char f2 = map[next_p2.y][next_p2.x]; // front two
    LOG("Try to push box: " << p1 << "\n");

    auto try_push = [&](pos a, pos b) {
        return can_push_box_vertical(map, dir, a, b, apply); // wrapper to save space
    };

    if ((BOTH_FREE(f1, f2)) || 
        (LEFT_FREE_AND_RIGHT_BOX(f1, f2) && try_push(next_p2, next_p2 + RIGHT)) ||
        (LEFT_BOX_AND_RIGHT_FREE(f1, f2) && try_push(next_p1 + LEFT, next_p1)) ||
        (BOTH_ONE_BOX(f1, f2) && try_push(next_p1, next_p2)) ||
        (BOTH_TWO_BOX(f1, f2) && try_push(next_p2, next_p2 + RIGHT) && try_push(next_p1 + LEFT, next_p1)))
    {
        if (apply)
        {
            map[p1.y][p1.x] = '.';
            map[p2.y][p2.x] = '.';
            map[next_p1.y][next_p1.x] = '[';
            map[next_p2.y][next_p2.x] = ']';
        }
            
        LOG("Can Push\n");
        return true;
    }
    LOG("Can't Push\n");
    return false;
}

void try_move_bot2(vector<vector<char>> &map, char move, pos &p)
{
    pos dir = get_dir(move);

    pos new_pos = p + dir;
    if (map[new_pos.y][new_pos.x] == '.')
        move_bot(map, dir, p);
    else if (IS_BOX(map[new_pos.y][new_pos.x]))
    {
        if (dir == LEFT || dir == RIGHT)
        {
            int len = 0;
            while (IS_BOX(map[new_pos.y][new_pos.x + len * dir.x])) // len * dir.x to get the sign
                len += 1;
            if (map[new_pos.y][new_pos.x + len * dir.x] == '.')
            {
                LOG("Found line of boxes of len: " << len << " that can be moved\n");
                char * box_start = &(map[new_pos.y][new_pos.x]);
                if (dir.x == -1)
                    box_start = box_start - len + 1;
                std::memmove(box_start + dir.x, box_start, len);
                move_bot(map, dir, p);
            }
        }
        else if (dir == UP || dir == DOWN)
        {
            pos p1 = new_pos, p2 = new_pos;
            if (map[new_pos.y][new_pos.x] == '[')
                p2 = new_pos + RIGHT;
            if (map[new_pos.y][new_pos.x] == ']')
                p1 = new_pos + LEFT;
            LOG("Try to move box Vertically\n");
            if (can_push_box_vertical(map, dir, p1, p2, false))
            {
                can_push_box_vertical(map, dir, p1, p2, true);
                move_bot(map, dir, p);
            }
        }
    }
}

size_t count_gps_map2(vector<vector<char>> &map)
{
    size_t result = 0;
    for (int i = 0; i < map.size(); i++)
        for (int j = 0; j < map[i].size(); j++)
            if (map[i][j] == '[') result += 100 * i + j;
    return result;
}

void part_two(vector<vector<char>> map, string moves)
{
    pos bot_pos = get_bot_pos(map);
    print_map(map);
    for (char move : moves)
    {
        LOG("Move: " << move << "\n");
        try_move_bot2(map, move, bot_pos);
        print_map(map);
    }
    std::cout << "Part two: " << count_gps_map2(map) << std::endl;
}

void double_push(vector<char> &row, char a, char b)
{
    row.push_back(a);
    row.push_back(b);
}

vector<char> create_map2_row(string line)
{
    vector<char> row;
    for(char c : line)
    {
        if (c == '@')       double_push(row, '@', '.');
        else if (c == 'O')  double_push(row, '[', ']');
        else if (c == '#')  double_push(row, '#', '#');
        else if (c == '.')  double_push(row, '.', '.');
    }
    return row;
}


#include <iostream>
#include <termios.h>
#include <unistd.h>

// Put terminal in raw mode (no enter needed)
void set_raw_mode(bool enable)
{
    static struct termios oldt, newt;
    if (enable)
    {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // disable canonical mode & echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    else
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

void live(vector<vector<char>> &map)
{
    pos bot_pos = get_bot_pos(map);
    print_map(map);
    set_raw_mode(true);
    char c;
    while (true)
    {
        if (read(STDIN_FILENO, &c, 1) > 0)
        {
            if (c == '\x1b') exit(EXIT_SUCCESS); // quit on ESC
            if (c == 'z') c = '^';
            else if (c == 's') c = 'v';
            else if (c == 'q') c = '<';
            else if (c == 'd') c = '>';
            LOG("Move: " << c << "\n");
            try_move_bot2(map, c, bot_pos);
            print_map(map);
        }
    }
    set_raw_mode(false);
}

int main() {
    std::ifstream file("input.txt");
    string line;
    string moves;
    vector<vector<char>> map;
    vector<vector<char>> map2;
    while (std::getline(file, line)) {
        if (line.empty())
            break;
        map.push_back(vector<char>(line.begin(), line.end()));
        map2.push_back(create_map2_row(line));
    }

    // live(map2);

    while (std::getline(file, line)) {
        moves += line;
    }
    // print_map(map);
    part_one(map, moves);
    part_two(map2, moves);
}