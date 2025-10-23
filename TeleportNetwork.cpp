#include "TeleportNetwork.h"
#include <iostream>

TeleportNetwork::TeleportNetwork() {
}

void TeleportNetwork::addTeleport(const Point& location, int teleportID) {
    locationToID.insert(location, teleportID);

    // Lấy danh sách hiện tại hoặc tạo mới
    DynamicArray<Point> locations;
    if (idToLocations.find(teleportID, locations)) {
        locations.push_back(location);
        idToLocations.insert(teleportID, locations);
    }
    else {
        DynamicArray<Point> newLocations;
        newLocations.push_back(location);
        idToLocations.insert(teleportID, newLocations);
    }

    std::cout << "Added teleport at (" << location.getX() << "," << location.getY()
        << ") with ID: " << teleportID << std::endl;
}

Point TeleportNetwork::getDestination(const Point& from) {
    int id;
    if (!locationToID.find(from, id)) {
        return from; // Không phải cổng teleport
    }

    DynamicArray<Point> destinations;
    if (!idToLocations.find(id, destinations) || destinations.getSize() <= 1) {
        std::cout << "⚠️ Khong co cong dich de teleport!" << std::endl;
        return from;
    }

    // Tìm cổng đích (không phải cổng hiện tại)
    for (int i = 0; i < destinations.getSize(); i++) {
        if (destinations[i] != from) {
            std::cout << "🌀 Teleporting from (" << from.getX() << "," << from.getY()
                << ") to (" << destinations[i].getX() << "," << destinations[i].getY()
                << ")" << std::endl;
            return destinations[i];
        }
    }

    return from;
}

bool TeleportNetwork::isTeleport(const Point& location) const {
    return locationToID.contains(location);
}

int TeleportNetwork::getTeleportID(const Point& location) const {
    int id;
    if (locationToID.find(location, id)) {
        return id;
    }
    return -1;
}

DynamicArray<Point> TeleportNetwork::getLinkedTeleports(int teleportID) const {
    DynamicArray<Point> result;
    idToLocations.find(teleportID, result);
    return result;
}

void TeleportNetwork::clear() {
    locationToID.clear();
    idToLocations.clear();
}

void TeleportNetwork::printNetwork() const {
    std::cout << "\n=== Teleport Network ===" << std::endl;

    // Iterate through idToLocations
    for (auto it = idToLocations.begin(); it != idToLocations.end(); ++it) {
        std::cout << "ID " << it->key << ": ";
        const DynamicArray<Point>& locations = it->value;
        for (int i = 0; i < locations.getSize(); i++) {
            std::cout << "(" << locations[i].getX() << "," << locations[i].getY() << ") ";
        }
        std::cout << std::endl;
    }
    std::cout << "======================\n" << std::endl;
}