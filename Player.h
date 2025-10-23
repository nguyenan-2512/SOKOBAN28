#pragma once
#include "GameObject.h"
#include "Animation.h"

class Player : public GameObject {
private:
    Animation animation;  // Object Animation (không phải con trỏ)

    int currentState;     // Trạng thái hiện tại (0-3)

public:
    Player(int x = 0, int y = 0, int tileSize = 32);

    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime);  // Thêm tham số deltaTime

    // Hàm khởi tạo animation
    void initAnimation(const sf::Texture& spriteSheet,
        int frameWidth,
        int frameHeight,
        int numFrames);

    // Hàm di chuyển với direction
    void move(int dx, int dy);

    // Override setPosition
    void setPosition(int x, int y, int dx, int dy);
};