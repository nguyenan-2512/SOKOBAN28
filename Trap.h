#pragma once
#include "GameObject.h"

class Trap : public GameObject {
private:
    bool isActive;  // Bẫy có đang hoạt động không
    const sf::Texture* activeTexture;   // Hình bẫy hoạt động
    const sf::Texture* inactiveTexture; // Hình bẫy tắt

public:
    Trap(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;

    void setActive(bool active);
    bool getIsActive() const { return isActive; }

    void setActiveTexture(const sf::Texture& texture);
    void setInactiveTexture(const sf::Texture& texture);
    void updateTexture();
}; 