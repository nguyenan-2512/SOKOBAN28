#pragma once	
#include <cstddef> 
class Point {
private:
	int x;
	int y;
public:
	Point(int = 0, int = 0);
	~Point();
	int getX() const;
	int getY() const;
	void setX(int);
	void setY(int);
	void setXY(int, int);
	bool operator==(const Point& other) const;
	bool operator!=(const Point& other) const;
};
struct PointHash {
    std::size_t operator()(const Point& p) const {
        int x = p.getX();
        int y = p.getY();

        unsigned int ux = (x >= 0) ? (2 * x) : (-2 * x - 1);
        unsigned int uy = (y >= 0) ? (2 * y) : (-2 * y - 1);

        // Szudzik's pairing function
        if (ux >= uy) {
            return ux * ux + ux + uy;
        }
        else {
            return uy * uy + ux;
        }
    }
};
struct IntHash {
    std::size_t operator()(int x) const {
        unsigned int ux = (x >= 0) ? static_cast<unsigned int>(x) : static_cast<unsigned int>(-x);
        ux = ((ux >> 16) ^ ux) * 0x45d9f3b;
        ux = ((ux >> 16) ^ ux) * 0x45d9f3b;
        ux = (ux >> 16) ^ ux;
        return ux;
    }
};