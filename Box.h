#pragma once
#include "GameObject.h"

class Box : public GameObject {
private:
    bool isOnGoal;
    const sf::Texture* normalTexture;
    const sf::Texture* goalTexture;

public:
    Box(int x, int y, int tileSize);
    void draw(sf::RenderWindow& window) override;
    void setOnGoal(bool onGoal);
    bool getIsOnGoal() const;
    void setNormalTexture(const sf::Texture& texture);
    void setGoalTexture(const sf::Texture& texture);
    void updateTexture();
};