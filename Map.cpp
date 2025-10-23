#include "Map.h"
#include <fstream>
#include <iostream>
#include <algorithm> // for std::any_of

Map::Map(const std::string& filename, int tileSize)
    : tileSize(tileSize), player(nullptr), isGameOver(false) {

    // Load tất cả textures
    if (!wallTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\da1.png")) {
        std::cerr << "Failed to load wall texture!" << std::endl;
    }
    if (!playerSpriteSheet.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\playersheet2.png")) {
        std::cerr << "Failed to load player texture!" << std::endl;
    }
    if (!floorTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\co.png")) {
        std::cerr << "Failed to load floor texture!" << std::endl;
    }
    if (!boxTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\thunggo.png")) {
        std::cerr << "Failed to load box texture!" << std::endl;
    }

   
    if (!ironBoxTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\thungsat.png")) {
        std::cerr << "Failed to load iron box texture! Using normal box texture." << std::endl;
        ironBoxTexture = boxTexture; // Tạm dùng box texture nếu chưa có
    }

    if (!waterTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\nuoc222.png")) {
        std::cerr << "Failed to load water texture!" << std::endl;
    }
    if (!bridgeTTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\caudoc.png")) {
        std::cerr << "Failed to load caudoc texture!" << std::endl;
    }
    if (!sandTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\cat.png")) {
        std::cerr << "Failed to load cat texture!" << std::endl;
    }

    // Trap
    if (!trapActiveTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\bay.png")) {
        std::cerr << "Failed to load bay texture!" << std::endl;
    }
    if (!trapInactiveTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\huynutbam.png")) {
        std::cerr << "Failed to load ko bay texture!" << std::endl;
    }

    // Button
    if (!buttonUnpressedTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\konutbam1.png")) {
        std::cerr << "Failed to load khong nut bam texture!" << std::endl;
    }
    if (!buttonPressedTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\nutbam1.png")) {
        std::cerr << "Failed to load nut bam texture!" << std::endl;
    }

    if (!boxOnGoalTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\godung.png")) {
        std::cerr << "Failed to load box on goal texture! Using normal box texture." << std::endl;
        boxOnGoalTexture = boxTexture;
    }

    if (!goalTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\vitridat.png")) {
        std::cerr << "Failed to load goal texture!" << std::endl;
    }

    if (!obstacleTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\bay.png")) {
        std::cerr << "Failed to load obstacle texture!" << std::endl;
    }
    if (!teleportActiveTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\teleport_active.png")) {
        std::cerr << "Failed to load teleport active texture!" << std::endl;
    }
    /*if (!teleportInactiveTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\teleport_inactive.png")) {
        std::cerr << "Failed to load teleport inactive texture!" << std::endl;
    }*/

    // Đọc file map
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Khong the mo file map: " << filename << std::endl;
        return;
    }

    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        for (int x = 0; x < (int)line.size(); x++) {
            char c = line[x];

            if (c == '#') {
                walls.emplace_back(x, y, tileSize);
                walls.back().setTexture(wallTexture);
            }
            else if (c == '=') {
                bridgeTs.emplace_back(x, y, tileSize);
                bridgeTs.back().setTexture(bridgeTTexture);
            }
            else if (c == '?') {
                sands.emplace_back(x, y, tileSize);
                sands.back().setTexture(sandTexture);
            }
            else if (c == '~') {
                waters.emplace_back(x, y, tileSize);
                waters.back().setTexture(waterTexture);
            }
            else if (c == '@') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                player = new Player(x, y, tileSize);
                player->initAnimation(playerSpriteSheet, 32, 32, 4);
            }
            else if (c == '$') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                boxes.emplace_back(x, y, tileSize);
                boxes.back().setNormalTexture(boxTexture);
                boxes.back().setGoalTexture(boxOnGoalTexture);
            }
            else if (c == 'I') { // Thùng sắt -ký tự 'I' (Iron)
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                ironBoxes.emplace_back(x, y, tileSize);
                ironBoxes.back().setIronTexture(ironBoxTexture);
            }
            else if (c == 'X' || c == 'x') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                goals.emplace_back(x, y, tileSize);
                goals.back().setTexture(goalTexture);
            }
            else if (c == 'O' || c == 'o') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                obstacles.emplace_back(x, y, tileSize);
                obstacles.back().setTexture(obstacleTexture);
            }
            else if (c == '+') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                goals.emplace_back(x, y, tileSize);
                goals.back().setTexture(goalTexture);
                player = new Player(x, y, tileSize);
                player->initAnimation(playerSpriteSheet, 32, 32, 4);
            }
            else if (c == '*') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                goals.emplace_back(x, y, tileSize);
                goals.back().setTexture(goalTexture);
                boxes.emplace_back(x, y, tileSize);
                boxes.back().setNormalTexture(boxTexture);
                boxes.back().setGoalTexture(boxOnGoalTexture);
                boxes.back().setOnGoal(true);
            }
            else if (c == '.' || c == ' ') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
            }
            else if (c == 'T') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                traps.emplace_back(x, y, tileSize);
                traps.back().setActiveTexture(trapActiveTexture);
                traps.back().setInactiveTexture(trapInactiveTexture);
            }
            else if (c == 'B') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
                buttons.emplace_back(x, y, tileSize);
                buttons.back().setUnpressedTexture(buttonUnpressedTexture);
                buttons.back().setPressedTexture(buttonPressedTexture);
            }
            else if (isdigit(c)) {
                int id = c - '0'; // Chuyển '1' -> 1, '2' -> 2, etc.

                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);

                teleports.emplace_back(x, y, tileSize, id);
                teleports.back().setTexture(teleportActiveTexture);


                teleportNetwork.addTeleport(Point(x, y), id);

                std::cout << ">>Teleport added at (" << x << "," << y
                    << ") with ID=" << id << std::endl;
            }
        }
        y++;
    }
    file.close();

    // LOGIC MỚI: Liên kết button với NHIỀU trap
    // Quy tắc: Nếu có N button và M trap
    // - Button 1 điều khiển M trap đầu tiên
    // - Button 2 điều khiển M trap tiếp theo
    // - ...

    int numButtons = buttons.size();
    int numTraps = traps.size();

    if (numButtons > 0 && numTraps > 0) {
        int trapsPerButton = numTraps / numButtons; // Số trap mỗi button điều khiển
        int remainder = numTraps % numButtons;      // Trap dư

        int trapIndex = 0;
        for (int i = 0; i < numButtons; i++) {
            int trapsForThisButton = trapsPerButton + (i < remainder ? 1 : 0);

            for (int j = 0; j < trapsForThisButton && trapIndex < numTraps; j++) {
                buttons[i].addLinkedTrap(traps[trapIndex].getX(), traps[trapIndex].getY());
                trapIndex++;
            }

            std::cout << "Button " << (i + 1) << " dieu khien " << trapsForThisButton << " trap" << std::endl;
        }
    }

    updateBoxStates();
    checkButtonStates();
}

Map::~Map() {
    delete player;
}





void Map::draw(sf::RenderWindow& window) {
    for (auto& floor : floors) floor.draw(window);
    for (auto& water : waters) water.draw(window);
    for (auto& sand : sands) sand.draw(window);
    for (auto& bridgeT : bridgeTs) bridgeT.draw(window);
    for (auto& goal : goals) goal.draw(window);
    for (auto& teleport : teleports) teleport.draw(window);
    for (auto& button : buttons) button.draw(window);
    for (auto& trap : traps) trap.draw(window);
    for (auto& obstacle : obstacles) obstacle.draw(window);
    for (auto& wall : walls) wall.draw(window);
    for (auto& box : boxes) box.draw(window);
    for (auto& ironBox : ironBoxes) ironBox.draw(window);

    if (player) player->draw(window);
}

Player* Map::getPlayer() {
    return player;
}

bool Map::isTrap(int x, int y) const {
    return std::any_of(traps.begin(), traps.end(),
        [x, y](const Trap& trap) {
            return trap.getX() == x && trap.getY() == y;
        });
}

bool Map::isButton(int x, int y) const {
    return std::any_of(buttons.begin(), buttons.end(),
        [x, y](const Button& button) {
            return button.getX() == x && button.getY() == y;
        });
}

Trap* Map::getTrapAt(int x, int y) {
    for (auto& trap : traps) {
        if (trap.getX() == x && trap.getY() == y) {
            return &trap;
        }
    }
    return nullptr;
}

Button* Map::getButtonAt(int x, int y) {
    for (auto& button : buttons) {
        if (button.getX() == x && button.getY() == y) {
            return &button;
        }
    }
    return nullptr;
}

void Map::checkButtonStates() {
    for (auto& button : buttons) {
        int bx = button.getX();
        int by = button.getY();

        bool hasBox = isBox(bx, by);
        bool hasIronBox = isIronBox(bx, by);
        bool isPressed = hasBox || hasIronBox;

        button.setPressed(isPressed);

        const auto& linkedTraps = button.getLinkedTraps();

        for (const auto& trapPos : linkedTraps) {
            Trap* trap = getTrapAt(trapPos.first, trapPos.second);
            if (trap) {
                trap->setActive(!isPressed);
            }
        }
    }
}

bool Map::isWall(int x, int y) const {
    return std::any_of(walls.begin(), walls.end(),
        [x, y](const Wall& wall) {
            return wall.getX() == x && wall.getY() == y;
        });
}

bool Map::isWater(int x, int y) const {
    return std::any_of(waters.begin(), waters.end(),
        [x, y](const Water& water) {
            return water.getX() == x && water.getY() == y;
        });
}

bool Map::isSand(int x, int y) const {
    return std::any_of(sands.begin(), sands.end(),
        [x, y](const Sand& sand) {
            return sand.getX() == x && sand.getY() == y;
        });
}

bool Map::isBox(int x, int y) const {
    return std::any_of(boxes.begin(), boxes.end(),
        [x, y](const Box& box) {
            return box.getX() == x && box.getY() == y;
        });
}

bool Map::isIronBox(int x, int y) const {
    return std::any_of(ironBoxes.begin(), ironBoxes.end(),
        [x, y](const IronBox& ironBox) {
            return ironBox.getX() == x && ironBox.getY() == y;
        });
}

bool Map::isObstacle(int x, int y) const {
    return std::any_of(obstacles.begin(), obstacles.end(),
        [x, y](const Obstacle& obstacle) {
            return obstacle.getX() == x && obstacle.getY() == y;
        });
}

bool Map::isGoal(int x, int y) const {
    return std::any_of(goals.begin(), goals.end(),
        [x, y](const Goal& goal) {
            return goal.getX() == x && goal.getY() == y;
        });
}

Box* Map::getBoxAt(int x, int y) {
    for (auto& box : boxes) {
        if (box.getX() == x && box.getY() == y) {
            return &box;
        }
    }
    return nullptr;
}

IronBox* Map::getIronBoxAt(int x, int y) {
    for (auto& ironBox : ironBoxes) {
        if (ironBox.getX() == x && ironBox.getY() == y) {
            return &ironBox;
        }
    }
    return nullptr;
}

bool Map::isValidMove(int x, int y) {
    if (isWall(x, y) || isObstacle(x, y) || isWater(x, y)) {
        return false;
    }
    return true;
}

bool Map::moveBox(Box* box, int dx, int dy) {
    int newX = box->getX() + dx;
    int newY = box->getY() + dy;

    Trap* trap = getTrapAt(newX, newY);
    if (trap && trap->getIsActive()) {
        return false;
    }

    if (!isWall(newX, newY) && !isObstacle(newX, newY) &&
        !isBox(newX, newY) && !isIronBox(newX, newY) && !isWater(newX, newY)) {
        box->setPosition(newX, newY);
        updateBoxStates();
        checkButtonStates();
        return true;
    }
    return false;
}

bool Map::moveIronBox(IronBox* ironBox, int dx, int dy) {
    int newX = ironBox->getX() + dx;
    int newY = ironBox->getY() + dy;

    Trap* trap = getTrapAt(newX, newY);
    if (trap && trap->getIsActive()) {
        return false;
    }

    if (!isWall(newX, newY) && !isObstacle(newX, newY) &&
        !isBox(newX, newY) && !isIronBox(newX, newY) && !isWater(newX, newY)) {
        ironBox->setPosition(newX, newY);
        checkButtonStates();
        return true;
    }
    return false;
}

bool Map::tryMovePlayer(int dx, int dy) {
    if (!player || isGameOver) return false;

    int newX = player->getX() + dx;
    int newY = player->getY() + dy;

    if (isWall(newX, newY) || isObstacle(newX, newY) || isWater(newX, newY)) {
        return false;
    }

    Trap* trap = getTrapAt(newX, newY);
    if (trap && trap->getIsActive()) {
        std::cout << "Ban da bi bay! Game Over!" << std::endl;
        isGameOver = true;
        return false;
    }

    Box* box = getBoxAt(newX, newY);
    if (box) {
        if (!moveBox(box, dx, dy)) {
            return false;
        }
    }

    IronBox* ironBox = getIronBoxAt(newX, newY);
    if (ironBox) {
        if (!moveIronBox(ironBox, dx, dy)) {
            return false;
        }
    }

    saveState();
    player->setPosition(newX, newY, dx, dy);
    if (isTeleport(newX, newY)) {
        std::cout << "Ban dang dung tren cong teleport! Nhan phim T de dich chuyen!" << std::endl;
    }

    checkButtonStates();
    return true;
}

void Map::updateBoxStates() {
    for (auto& box : boxes) {
        bool onGoal = isGoal(box.getX(), box.getY());
        box.setOnGoal(onGoal);
    }
}

bool Map::checkWin() const {
    for (const auto& box : boxes) {
        bool onGoal = false;
        for (const auto& goal : goals) {
            if (box.getX() == goal.getX() && box.getY() == goal.getY()) {
                onGoal = true;
                break;
            }
        }
        if (!onGoal) return false;
    }
    return boxes.size() > 0 && boxes.size() == goals.size();
}




void Map::saveState() {
    MoveState state = getCurrentState();
    moveHistory.push(state);
}

MoveState Map::getCurrentState() const {
    Point playerPos = player->getPosition();
    std::vector<Point> boxPos;

    for (const auto& box : boxes) {
        boxPos.push_back(box.getPosition());
    }

    return MoveState(playerPos, boxPos);
}

void Map::restoreState(const MoveState& state) {
    player->setPosition(state.playerPosition.getX(), state.playerPosition.getY(), 0, 0);

    for (size_t i = 0; i < boxes.size() && i < state.boxPositions.size(); i++) {
        boxes[i].setPosition(state.boxPositions[i].getX(), state.boxPositions[i].getY());
    }

    updateBoxStates();  // Cập nhật trạng thái sau khi restore
}

void Map::undo() {
    if (moveHistory.empty()) {
        std::cout << "Khong co nuoc di nao de undo!" << std::endl;
        return;
    }

    MoveState previousState = moveHistory.top();
    moveHistory.pop();

    restoreState(previousState);

    std::cout << "Da undo! Con lai " << moveHistory.size() << " nuoc di trong lich su." << std::endl;
}

int Map::getMoveCount() const {
    return (int)moveHistory.size();
}

bool Map::isTeleport(int x, int y) const {
    return std::any_of(teleports.begin(), teleports.end(),
        [x, y](const Teleport& tp) {
            return tp.getX() == x && tp.getY() == y;
        });
}
Teleport* Map::getTeleportAt(int x, int y) {
    for (auto& tp : teleports) {
        if (tp.getX() == x && tp.getY() == y) {
            return &tp;
        }
    }
    return nullptr;
}

bool Map::tryTeleport() {
    if (!player || isGameOver) {
        std::cout << " Khong the teleport!" << std::endl;
        return false;
    }

    int currentX = player->getX();
    int currentY = player->getY();
    Point currentPos(currentX, currentY);

    // Kiểm tra player có đứng trên cổng teleport không
    if (!teleportNetwork.isTeleport(currentPos)) {
        std::cout << "Ban khong dung tren cong teleport!" << std::endl;
        return false;
    }

    // Lấy điểm đến
    Point destination = teleportNetwork.getDestination(currentPos);

    // Kiểm tra có teleport thành công không
    if (destination == currentPos) {
        std::cout << "Khong co cong dich de teleport!" << std::endl;
        return false;
    }

    int destX = destination.getX();
    int destY = destination.getY();

    // Kiểm tra điểm đến có hợp lệ không (không có vật cản)
    if (isWall(destX, destY) || isObstacle(destX, destY) ||
        isBox(destX, destY) || isIronBox(destX, destY)) {
        std::cout << "Diem den bi chan! Khong the teleport!" << std::endl;
        return false;
    }

    // TELEPORT THÀNH CÔNG!
    saveState(); // Lưu state để có thể undo
    player->setPosition(destX, destY, 0, 0);

    std::cout << ">>Teleport thanh cong tu (" << currentX << "," << currentY
        << ") den (" << destX << "," << destY << ")!" << std::endl;

    checkButtonStates(); // Cập nhật trạng thái button/trap

    return true;
}