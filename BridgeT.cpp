#include "BridgeT.h"

BridgeT::BridgeT(int x, int y, int tileSize) : GameObject(x, y, tileSize) {
}

void BridgeT::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}