#include "Sand.h"

Sand::Sand(int x, int y, int tileSize) : GameObject(x, y, tileSize) {
}

void Sand::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}