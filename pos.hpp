
struct pos
{
	int x;
	int y;
    pos operator+(const pos& other) const {
        return {x + other.x, y + other.y};
    }

    pos operator-(const pos& other) const {
        return {x - other.x, y - other.y};
    }

    pos operator*(const pos& other) const {
        return {x * other.x, y * other.y};
    }

    pos operator*(const int other) const {
        return {x * other, y * other};
    }

	pos& operator+=(const pos& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    pos& operator-=(const pos& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

	bool operator==(const pos& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const pos& other) const {
        return !(*this == other);
    }

};