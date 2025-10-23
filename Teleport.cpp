#include "Teleport.h"

Teleport::Teleport(int x, int y, int tileSize, int id)
    : GameObject(x, y, tileSize),
    teleportID(id),
    texture(nullptr) {
}

void Teleport::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Teleport::setTexture(const sf::Texture& tex) {
    texture = &tex;
    sprite.setTexture(tex);
}
