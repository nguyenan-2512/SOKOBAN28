#pragma once
#include "GameObject.h"

// Thùng sắt - dùng để đè nút kích hoạt, không thể đưa lên goal
class IronBox : public GameObject {
private:
    const sf::Texture* texture;

public:
    IronBox(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;
    void setIronTexture(const sf::Texture& texture);
}; 