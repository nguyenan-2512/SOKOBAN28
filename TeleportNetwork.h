#pragma once
#include "Point.h"
#include "DynamicArray.h"  
#include "HashTable.h"     

//// Hash function cho Point để dùng trong unordered_map
//struct PointHash {
//    std::size_t operator()(const Point& p) const {
//        return std::hash<int>()(p.getX()) ^ (std::hash<int>()(p.getY()) << 1);
//    }
//};

class TeleportNetwork {
private:
    // Map từ vị trí -> Teleport ID
    HashTable<Point, int, PointHash> locationToID;

    // Map từ ID -> danh sách các vị trí cùng ID (cổng liên kết)
    HashTable<int, DynamicArray<Point>, IntHash> idToLocations;

public:
    TeleportNetwork();

    // Thêm cổng teleport
    void addTeleport(const Point& location, int teleportID);

    // Lấy điểm đến khi đi vào cổng
    Point getDestination(const Point& from);

    // Kiểm tra xem vị trí có phải cổng teleport không
    bool isTeleport(const Point& location) const;

    // Lấy ID của cổng tại vị trí
    int getTeleportID(const Point& location) const;

    // Lấy tất cả cổng cùng ID
    DynamicArray<Point> getLinkedTeleports(int teleportID) const;

    // Clear all
    void clear();

    // Debug: in thông tin mạng
    void printNetwork() const;
};