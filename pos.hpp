#include <iostream>

struct pos
{
	int x;
	int y;

    pos operator+(const pos& other) const { return {x + other.x, y + other.y}; }
    pos operator-(const pos& other) const { return {x - other.x, y - other.y}; }
    pos operator*(const pos& other) const { return {x * other.x, y * other.y}; }
    pos operator*(int other) const { return {x * other, y * other}; }
    pos& operator+=(const pos& other) { x += other.x; y += other.y; return *this; }
    pos& operator-=(const pos& other) { x -= other.x; y -= other.y; return *this; }
    bool operator==(const pos& other) const { return x == other.x && y == other.y; }
    bool operator!=(const pos& other) const { return !(*this == other); }
};

struct pos_hash {
    std::size_t operator()(const pos& p) const {
        // Simple combination of x and y into a hash
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

std::ostream& operator<<(std::ostream& os, const pos& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

#define UP		(pos){0, -1}
#define DOWN	(pos){0, 1}
#define LEFT	(pos){-1, 0}
#define RIGHT	(pos){1, 0}