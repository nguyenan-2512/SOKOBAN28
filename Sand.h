#pragma once
#include "GameObject.h"

class Sand : public GameObject {
public:
    Sand(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;
};