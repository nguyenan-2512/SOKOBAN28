#pragma once
#include "GameObject.h"
#include <string>

class Teleport : public GameObject {
private:
    int teleportID;  // ID để nhóm các cổng với nhau (cùng ID = liên kết)
    const sf::Texture* texture;

public:
    Teleport(int x, int y, int tileSize, int id);
    void draw(sf::RenderWindow& window) override;

    int getTeleportID() const { return teleportID; }
    void setTeleportID(int id) { teleportID = id; }
    void setTexture(const sf::Texture& texture);
};