
#include "IronBox.h"

IronBox::IronBox(int x, int y, int tileSize)
    : GameObject(x, y, tileSize),
    texture(nullptr) {
}

void IronBox::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void IronBox::setIronTexture(const sf::Texture& tex) {
    texture = &tex;
    sprite.setTexture(tex);
}