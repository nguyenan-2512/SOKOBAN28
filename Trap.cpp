#include "Trap.h"

Trap::Trap(int x, int y, int tileSize)
    : GameObject(x, y, tileSize),
    isActive(true),  // Mặc định bẫy hoạt động
    activeTexture(nullptr),
    inactiveTexture(nullptr) {
}

void Trap::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Trap::setActive(bool active) {
    isActive = active;
    updateTexture();
}

void Trap::setActiveTexture(const sf::Texture& texture) {
    activeTexture = &texture;
    if (isActive) {
        sprite.setTexture(texture);
    }
}

void Trap::setInactiveTexture(const sf::Texture& texture) {
    inactiveTexture = &texture;
    if (!isActive) {
        sprite.setTexture(texture);
    }
}

void Trap::updateTexture() {
    if (isActive && activeTexture) {
        sprite.setTexture(*activeTexture);
    }
    else if (!isActive && inactiveTexture) {
        sprite.setTexture(*inactiveTexture);
    }
}