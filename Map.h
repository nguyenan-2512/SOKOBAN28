#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <stack>
#include "Wall.h"
#include "Floor.h"
#include "Player.h"
#include "Box.h"
#include "Goal.h"
#include "Obstacle.h"
#include "Water.h"
#include "Sand.h"
#include "BridgeT.h"
#include "Trap.h"
#include "Button.h"
#include "IronBox.h"
#include "Teleport.h"
#include "TeleportNetwork.h"
#include "MoveState.h"

class Map {
private:
    int tileSize;
    Player* player;

    std::vector<Wall> walls;
    std::vector<Floor> floors;
    std::vector<Box> boxes;
    std::vector<IronBox> ironBoxes;
    std::vector<Goal> goals;
    std::vector<Obstacle> obstacles;
    std::vector<Water> waters;
    std::vector<Sand> sands;
    std::vector<BridgeT> bridgeTs;
    std::vector<Trap> traps;
    std::vector<Button> buttons;
    std::vector<Teleport> teleports;

    TeleportNetwork teleportNetwork;

    sf::Texture wallTexture;
    sf::Texture playerSpriteSheet;
    sf::Texture floorTexture;
    sf::Texture boxTexture;
    sf::Texture ironBoxTexture;
    sf::Texture boxOnGoalTexture;
    sf::Texture goalTexture;
    sf::Texture obstacleTexture;
    sf::Texture waterTexture;
    sf::Texture sandTexture;
    sf::Texture bridgeTTexture;
    sf::Texture trapActiveTexture;
    sf::Texture trapInactiveTexture;
    sf::Texture buttonUnpressedTexture;
    sf::Texture buttonPressedTexture;
    sf::Texture teleportActiveTexture;
    //sf::Texture teleportInactiveTexture;

    std::stack<MoveState> moveHistory;

    void updateBoxStates();
    void checkButtonStates();

public:
    Map(const std::string& filename, int tileSize);
    ~Map();

    void draw(sf::RenderWindow& window);
    bool tryMovePlayer(int dx, int dy);
    bool checkWin() const;
    Player* getPlayer();

    // Trap và Button
    bool isTrap(int x, int y) const;
    bool isButton(int x, int y) const;
    Trap* getTrapAt(int x, int y);
    Button* getButtonAt(int x, int y);

    // Teleport - THAY ĐỔI: Không tự động, phải gọi thủ công
    bool isTeleport(int x, int y) const;
    Teleport* getTeleportAt(int x, int y);
    bool tryTeleport(); // ✨ HÀM MỚI: Teleport thủ công
    TeleportNetwork& getTeleportNetwork() { return teleportNetwork; }

    // Kiểm tra vị trí
    bool isSand(int x, int y) const;
    bool isWall(int x, int y) const;
    bool isWater(int x, int y) const;
    bool isBox(int x, int y) const;
    bool isIronBox(int x, int y) const;
    bool isObstacle(int x, int y) const;
    bool isGoal(int x, int y) const;
    bool isValidMove(int x, int y);

    Box* getBoxAt(int x, int y);
    IronBox* getIronBoxAt(int x, int y);
    bool moveBox(Box* box, int dx, int dy);
    bool moveIronBox(IronBox* ironBox, int dx, int dy);

    // Undo
    void saveState();
    MoveState getCurrentState() const;
    void restoreState(const MoveState& state);
    void undo();
    int getMoveCount() const;

    // Game Over
    bool isGameOver;
    void setGameOver(bool value) { isGameOver = value; }
    bool getGameOver() const { return isGameOver; }
};