#include "Button.h"

Button::Button(int x, int y, int tileSize)
    : GameObject(x, y, tileSize),
    isPressed(false),
    unpressedTexture(nullptr),
    pressedTexture(nullptr) {
    // linkedTraps vector tự động khởi tạo rỗng
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Button::setPressed(bool pressed) {
    isPressed = pressed;
    updateTexture();
}

void Button::setUnpressedTexture(const sf::Texture& texture) {
    unpressedTexture = &texture;
    if (!isPressed) {
        sprite.setTexture(texture);
    }
}

void Button::setPressedTexture(const sf::Texture& texture) {
    pressedTexture = &texture;
    if (isPressed) {
        sprite.setTexture(texture);
    }
}

void Button::updateTexture() {
    if (isPressed && pressedTexture) {
        sprite.setTexture(*pressedTexture);
    }
    else if (!isPressed && unpressedTexture) {
        sprite.setTexture(*unpressedTexture);
    }
}