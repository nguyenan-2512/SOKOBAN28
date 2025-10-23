#include "Water.h"

Water::Water(int x, int y, int tileSize) : GameObject(x, y, tileSize) {
}

void Water::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}