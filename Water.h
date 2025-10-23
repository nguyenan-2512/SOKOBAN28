#pragma once
#include "GameObject.h"

class Water : public GameObject {
public:
    Water(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;
};