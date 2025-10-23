#pragma once
#include "GameObject.h"

class BridgeT : public GameObject {
public:
    BridgeT(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;
};