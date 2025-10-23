#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu() : selectedItem(0), currentState(MenuState::MENU) {
}

Menu::~Menu() {
}

bool Menu::loadResources() {
    // Load background texture
    if (!backgroundTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\menutext.png")) {
        std::cerr << "Failed to load menu background texture!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundTexture.setSmooth(true);

    // Load select map background
    if (!selectMapBackgroundTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\selectmaptext.png")) {
        std::cerr << "Failed to load select map background!" << std::endl;
    }
    selectMapBackgroundSprite.setTexture(selectMapBackgroundTexture);
    selectMapBackgroundTexture.setSmooth(true);


    // Load font
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Failed to load font, using default font" << std::endl;
    }

    setupButtons();
    setupTexts();

    return true;
}

void Menu::setupButtons() {
    // Setup Play button
    playButton.setSize(sf::Vector2f(270,90)); // Tăng kích thước để dễ click
    playButton.setPosition(275, 300); // Điều chỉnh vị trí theo ảnh
    playButton.setFillColor(sf::Color(0, 0, 0, 0)); // Trong suốt để hiển thị ảnh phía sau
    playButton.setOutlineThickness(0);

    // Setup Guide button (nếu cần - bạn nói sẽ cập nhật sau)
    guideButton.setSize(sf::Vector2f(270, 90));
    guideButton.setPosition(275, 454); // Điều chỉnh vị trí
    guideButton.setFillColor(sf::Color(0, 0, 0, 0));
    guideButton.setOutlineThickness(0);

    // Setup Exit button
    exitButton.setSize(sf::Vector2f(270, 90));
    exitButton.setPosition(275, 610);// Điều chỉnh vị trí
    exitButton.setFillColor(sf::Color(0, 0, 0, 0));
    exitButton.setOutlineThickness(0);
}
void Menu::setupTexts() {
    // KHÔNG CẦN TEXT vì ảnh đã có sẵn chữ PLAY, GUIDE, EXIT
    // Nhưng giữ lại để debug hoặc hiển thị hover effect nếu cần

    playText.setFont(font);
    playText.setString("");
    playText.setCharacterSize(0);

    exitText.setFont(font);
    exitText.setString("");
    exitText.setCharacterSize(0);
}

void Menu::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (currentState == MenuState::MENU) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (isMouseOverButton(playButton, mousePos)) {
                currentState = MenuState::SELECTION_MAP;
                setupMapItems(window);
            }
            else if (isMouseOverButton(guideButton, mousePos)) {
                // TODO: Hiển thị hướng dẫn - bạn sẽ cập nhật sau
                std::cout << "Guide button clicked - chua co chuc nang" << std::endl;
            }
            else if (isMouseOverButton(exitButton, mousePos)) {
                currentState = MenuState::EXIT;
            }
        }

        // Handle keyboard input
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Up:
                selectedItem = (selectedItem - 1 + 3) % 3; // 3 button: Play, Guide, Exit
                break;
            case sf::Keyboard::Down:
                selectedItem = (selectedItem + 1) % 3;
                break;
            case sf::Keyboard::Enter:
                if (selectedItem == 0) { // Play
                    currentState = MenuState::SELECTION_MAP;
                    setupMapItems(window);
                }
                else if (selectedItem == 1) { // Guide
                    std::cout << "Guide - chua co chuc nang" << std::endl;
                }
                else { // Exit
                    currentState = MenuState::EXIT;
                }
                break;
            case sf::Keyboard::Escape:
                currentState = MenuState::EXIT;
                break;
            }
        }

        // Handle mouse hover effects - HIỆU ỨNG KHI HOVER
        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (isMouseOverButton(playButton, mousePos)) {
                selectedItem = 0;
                playButton.setFillColor(sf::Color(255, 255, 255, 50)); // Hiệu ứng sáng nhẹ
            }
            else {
                playButton.setFillColor(sf::Color(0, 0, 0, 0));
            }

            if (isMouseOverButton(guideButton, mousePos)) {
                selectedItem = 1;
                guideButton.setFillColor(sf::Color(255, 255, 255, 50));
            }
            else {
                guideButton.setFillColor(sf::Color(0, 0, 0, 0));
            }

            if (isMouseOverButton(exitButton, mousePos)) {
                selectedItem = 2;
                exitButton.setFillColor(sf::Color(255, 255, 255, 50));
            }
            else {
                exitButton.setFillColor(sf::Color(0, 0, 0, 0));
            }
        }
    }

    else if (currentState == MenuState::SELECTION_MAP) {
        // Xử lý click chuột
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                std::cout << "CLICKED: X=" << mousePos.x << ", Y=" << mousePos.y << std::endl;
            }

            for (size_t i = 0; i < mapButtons.size(); ++i) {
                if (isMouseOverButton(mapButtons[i], mousePos)) {
                    selectedMap = static_cast<int>(i);
                    std::cout << "Selected Map: " << (i + 1) << std::endl;
                    currentState = MenuState::PLAYING;
                    break;
                }
            }
        }

        // Xử lý phím điều hướng
        if (event.type == sf::Event::KeyPressed) {
            const int numMaps = 10;

            switch (event.key.code) {
            case sf::Keyboard::Left:
            case sf::Keyboard::A:
                if (highlightedMapIndex % 4 > 0) { // 4 cột theo ảnh mới
                    highlightedMapIndex--;
                }
                break;

            case sf::Keyboard::Right:
            case sf::Keyboard::D:
                if (highlightedMapIndex % 4 < 3 && highlightedMapIndex < numMaps - 1) {
                    highlightedMapIndex++;
                }
                break;

            case sf::Keyboard::Up:
            case sf::Keyboard::W:
                if (highlightedMapIndex >= 4) {
                    highlightedMapIndex -= 4;
                }
                break;

            case sf::Keyboard::Down:
            case sf::Keyboard::S:
                if (highlightedMapIndex < 4 && highlightedMapIndex + 4 < numMaps) {
                    highlightedMapIndex += 4;
                }
                else if (highlightedMapIndex >= 4 && highlightedMapIndex < 8) {
                    highlightedMapIndex = std::min(highlightedMapIndex + 4, numMaps - 1);
                }
                break;

            case sf::Keyboard::Enter:
            case sf::Keyboard::Space:
                selectedMap = highlightedMapIndex;
                std::cout << "Selected Map: " << (selectedMap + 1) << std::endl;
                currentState = MenuState::PLAYING;
                break;

            case sf::Keyboard::Escape:
                currentState = MenuState::MENU;
                break;
            }
        }

        // Xử lý hover chuột
        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            for (size_t i = 0; i < mapButtons.size(); ++i) {
                if (isMouseOverButton(mapButtons[i], mousePos)) {
                    highlightedMapIndex = static_cast<int>(i);
                    break;
                }
            }
        }
    }
}

void Menu::update() {
    if (currentState == MenuState::MENU) {
        // Cập nhật hiệu ứng hover dựa trên selectedItem
        if (selectedItem == 0) {
            playButton.setFillColor(sf::Color(255, 255, 255, 50));
            guideButton.setFillColor(sf::Color(0, 0, 0, 0));
            exitButton.setFillColor(sf::Color(0, 0, 0, 0));
        }
        else if (selectedItem == 1) {
            playButton.setFillColor(sf::Color(0, 0, 0, 0));
            guideButton.setFillColor(sf::Color(255, 255, 255, 50));
            exitButton.setFillColor(sf::Color(0, 0, 0, 0));
        }
        else {
            playButton.setFillColor(sf::Color(0, 0, 0, 0));
            guideButton.setFillColor(sf::Color(0, 0, 0, 0));
            exitButton.setFillColor(sf::Color(255, 255, 255, 50));
        }
    }
}

void Menu::draw(sf::RenderWindow& window) {
    if (currentState == MenuState::MENU) {
        window.draw(backgroundSprite);

        // Vẽ các button trong suốt để bắt sự kiện click
        window.draw(playButton);
        window.draw(guideButton);
        window.draw(exitButton);

        // Không cần vẽ text vì ảnh đã có sẵn
    }
    else if (currentState == MenuState::SELECTION_MAP) {
        drawSelectionMap(window);
    }
}

MenuState Menu::getState() const {
    return currentState;
}

void Menu::setState(MenuState state) {
    currentState = state;
}

void Menu::reset() {
    currentState = MenuState::MENU;
    selectedItem = 0;
}

int Menu::getSelectedMap() const {
    return selectedMap;
}

bool Menu::isMouseOverButton(const sf::RectangleShape& button, sf::Vector2i mousePos) {
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}


void Menu::setupMapItems(sf::RenderWindow& window) {
    mapButtons.clear();
    mapItems.clear();
    highlightedMapIndex = 0;

    const int numMaps = 10;

    // === VỊ TRÍ CÁC NÚT THEO ẢNH CỦA BẠN ===
    // Dựa vào ảnh: 2 hàng x 4 cột
    // Các vị trí tôi đo từ ảnh của bạn:

    const float buttonRadius = 50.f;    // Bán kính nút tròn

    // Tọa độ tâm của từng nút (đo từ ảnh)
    // Hàng 1: Map 1-4
    std::vector<sf::Vector2f> positions = {
        {181.f, 302.f},  // Map 1
        {325.f, 302.f},  // Map 2
        {469.f, 302.f},  // Map 3
        {613.f, 302.f},  // Map 4
        {181.f, 481.f},  // Map 5
        {325.f, 481.f},  // Map 6
        {469.f, 481.f},  // Map 7
        {613.f, 481.f},  // Map 8
        {0.f, 0.f},      // Map 9 (nếu có)
        {0.f, 0.f}       // Map 10 (nếu có)
    };

    for (int i = 0; i < numMaps && i < 8; ++i) {
        // Tạo hình tròn thay vì hình vuông
        sf::CircleShape btn(buttonRadius);
        btn.setFillColor(sf::Color(0, 0, 0, 0)); // Trong suốt
        btn.setOutlineColor(sf::Color::Yellow);
        btn.setOutlineThickness(0.f);

        // Đặt origin ở tâm để dễ căn chỉnh
        btn.setOrigin(buttonRadius, buttonRadius);
        btn.setPosition(positions[i]);

        // Chuyển CircleShape thành RectangleShape để lưu (hoặc dùng CircleShape)
        // Nhưng vì bạn đang dùng vector<RectangleShape>, ta tạo rect bao quanh
        sf::RectangleShape rectBtn;
        rectBtn.setSize(sf::Vector2f(buttonRadius * 2, buttonRadius * 2));
        rectBtn.setFillColor(sf::Color(0, 0, 0, 0));
        rectBtn.setOutlineColor(sf::Color::Yellow);
        rectBtn.setOutlineThickness(0.f);
        rectBtn.setOrigin(buttonRadius, buttonRadius);
        rectBtn.setPosition(positions[i]);

        // Tạo số (không hiển thị vì ảnh đã có)
        sf::Text num;
        num.setFont(font);
        num.setString("");
        num.setCharacterSize(0);

        mapButtons.push_back(rectBtn);
        mapItems.push_back(num);
    }
}

void Menu::drawSelectionMap(sf::RenderWindow& window) {
    window.draw(selectMapBackgroundSprite);

    // Vẽ highlight cho nút được chọn - VÒNG TRÒN CHUYÊN NGHIỆP
    if (highlightedMapIndex >= 0 && highlightedMapIndex < (int)mapButtons.size()) {
        sf::Vector2f btnPos = mapButtons[highlightedMapIndex].getPosition();
        float radius = 55.f; // Bán kính vòng tròn highlight

        // Vẽ 3 vòng tròn để tạo hiệu ứng glow
        for (int i = 0; i < 3; ++i) {
            sf::CircleShape highlight(radius + i * 8.f);
            highlight.setOrigin(radius + i * 8.f, radius + i * 8.f);
            highlight.setPosition(btnPos);
            highlight.setFillColor(sf::Color(255, 255, 0, 50 - i * 15)); // Vàng mờ dần
            highlight.setOutlineThickness(3.f - i);
            highlight.setOutlineColor(sf::Color(255, 255, 0, 150 - i * 40));
            window.draw(highlight);
        }

        // Vòng tròn chính - viền vàng sáng
        sf::CircleShape mainHighlight(radius);
        mainHighlight.setOrigin(radius, radius);
        mainHighlight.setPosition(btnPos);
        mainHighlight.setFillColor(sf::Color(255, 255, 100, 80)); // Vàng trong suốt
        mainHighlight.setOutlineThickness(4.f);
        mainHighlight.setOutlineColor(sf::Color::Yellow); // Vàng sáng
        window.draw(mainHighlight);
    }

    // Hiển thị hướng dẫn
    sf::Text note;
    note.setFont(font);
    note.setString("Dung phim mui ten hoac click chuot de chon | Enter de xac nhan | ESC de quay lai");
    note.setCharacterSize(16);
    note.setFillColor(sf::Color::White);
    note.setStyle(sf::Text::Bold);
    note.setOutlineColor(sf::Color::Black);
    note.setOutlineThickness(2.f);

    sf::FloatRect noteBounds = note.getLocalBounds();
    note.setPosition(400.f - noteBounds.width / 2.f, 550.f);
    window.draw(note);
}