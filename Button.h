#pragma once
#include "GameObject.h"
#include <vector>
#include <utility> // for std::pair

class Button : public GameObject {
private:
    bool isPressed;
    std::vector<std::pair<int, int>> linkedTraps; // Danh sách tọa độ các trap liên kết (x, y)
    const sf::Texture* unpressedTexture;
    const sf::Texture* pressedTexture;

public:
    Button(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;

    void setPressed(bool pressed);
    bool getIsPressed() const { return isPressed; }

    // Thêm 1 trap vào danh sách liên kết
    void addLinkedTrap(int x, int y) {
        linkedTraps.push_back(std::make_pair(x, y));
    }

    // Lấy danh sách tất cả trap liên kết
    const std::vector<std::pair<int, int>>& getLinkedTraps() const {
        return linkedTraps;
    }

    void setUnpressedTexture(const sf::Texture& texture);
    void setPressedTexture(const sf::Texture& texture);
    void updateTexture();
};