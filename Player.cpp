#include "Player.h"

Player::Player(int x, int y, int tileSize)
    : GameObject(x, y, tileSize),
    currentState(Animation::MOVE_DOWN) {  // Mặc định nhìn xuống
}

void Player::initAnimation(const sf::Texture& spriteSheet,
    int frameWidth,
    int frameHeight,
    int numFrames) {
    // Tạo Animation object
    animation = Animation(&sprite, spriteSheet, frameWidth, frameHeight, numFrames, true);

    if (frameWidth != tileSize || frameHeight != tileSize) {
        float scaleX = (float)tileSize / frameWidth;
        float scaleY = (float)tileSize / frameHeight;
        sprite.setScale(scaleX, scaleY);
    }
}

void Player::update(float deltaTime) {
    // Cập nhật animation
    animation.update(currentState, deltaTime);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::move(int dx, int dy) {
    // Xác định hướng di chuyển
    if (dy < 0) {
        currentState = Animation::MOVE_UP;     // Lên
    }
    else if (dy > 0) {
        currentState = Animation::MOVE_DOWN;   // Xuống
    }
    else if (dx < 0) {
        currentState = Animation::MOVE_LEFT;   // Trái
    }
    else if (dx > 0) {
        currentState = Animation::MOVE_RIGHT;  // Phải
    }
}

void Player::setPosition(int x, int y, int dx, int dy) {
    // Đổi hướng trước
    move(dx, dy);

    // Di chuyển
    GameObject::setPosition(x, y);
}