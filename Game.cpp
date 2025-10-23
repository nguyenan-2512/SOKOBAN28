#include "Game.h"
#include <iostream>
using namespace std;

sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
Game::Game() : window(sf::VideoMode(800, 800), "Sokoban", sf::Style::Default),

currentMap(nullptr),
gameState(GameState::MENU),
showWinMessage(false),
showGameOverMessage(false) {
    window.setFramerateLimit(60);
    Animation::animationSpeed = 0.1f;

    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    backgroundSprite.setScale(
        float(windowSize.x) / textureSize.x,
        float(windowSize.y) / textureSize.y
    );

    if (!backgroundMusic.openFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\hi.ogg")) {
        cerr << "Failed to load background music!" << endl;
    }

    if (!moveSoundBuffer.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\step.ogg")) {
        cerr << "Failed to load move sound!" << endl;
    }
    moveSound.setBuffer(moveSoundBuffer);

    if (!winSoundBuffer.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\win.ogg")) {
        cerr << "Failed to load win sound!" << endl;
    }
    winSound.setBuffer(winSoundBuffer);

    // Load Game Over sound
    if (!gameOverSoundBuffer.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\gameover.ogg")) {
        cerr << "Failed to load game over sound!" << endl;
    }
    gameOverSound.setBuffer(gameOverSoundBuffer);

    if (!winTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\win.png")) {
        cerr << "Failed to load win message texture!" << endl;
        winTexture.create(800, 600);
        sf::Uint8* pixels = new sf::Uint8[800 * 600 * 4];
        for (int i = 0; i < 800 * 600 * 4; i += 4) {
            pixels[i] = 50; pixels[i + 1] = 80; pixels[i + 2] = 120; pixels[i + 3] = 255;
        }
        winTexture.update(pixels);
        delete[] pixels;
    }
    winSprite.setTexture(winTexture);
    winSprite.setPosition(0, 0);

    // Load Game Over texture
    if (!gameOverTexture.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\gameover.png")) {
        cerr << "Failed to load game over texture! Creating default..." << endl;
        gameOverTexture.create(800, 600);
        sf::Uint8* pixels = new sf::Uint8[800 * 600 * 4];
        for (int i = 0; i < 800 * 600 * 4; i += 4) {
            pixels[i] = 120; pixels[i + 1] = 50; pixels[i + 2] = 50; pixels[i + 3] = 255;
        }
        gameOverTexture.update(pixels);
        delete[] pixels;
    }
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(0, 0);

    menu.loadResources();
}

Game::~Game() {
    cleanupGame();
}

void Game::run() {
    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (gameState == GameState::MENU) {
            menu.handleEvent(event, window);
        }
        else if (gameState == GameState::PLAYING) {
            if (showWinMessage || showGameOverMessage) {
                if (event.type == sf::Event::KeyPressed) {
                    gameState = GameState::MENU;
                    menu.setState(MenuState::MENU);
                    cleanupGame();
                    showWinMessage = false;
                    showGameOverMessage = false;
                    backgroundMusic.play();
                }
            }
            else {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        gameState = GameState::MENU;
                        menu.setState(MenuState::MENU);
                        cleanupGame();
                    }
                    else if (event.key.code == sf::Keyboard::R) {
                        initializeGame();
                    }
                    else if (event.key.code == sf::Keyboard::U) {
                        if (currentMap) {
                            currentMap->undo();
                            cout << "Undo! Con lai " << currentMap->getMoveCount() << " nuoc di." << endl;
                        }
                    }
                    // ✨ THÊM PHÍM T ĐỂ TELEPORT
                    else if (event.key.code == sf::Keyboard::T) {
                        if (currentMap) {
                            bool teleported = currentMap->tryTeleport();
                            if (teleported) {
                                playMoveSound(); // Phát âm thanh khi teleport
                            }
                        }
                    }
                    else if (currentMap) {
                        bool moved = false;
                        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                            moved = currentMap->tryMovePlayer(0, -1);
                        }
                        else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                            moved = currentMap->tryMovePlayer(0, 1);
                        }
                        else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                            moved = currentMap->tryMovePlayer(-1, 0);
                        }
                        else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                            moved = currentMap->tryMovePlayer(1, 0);
                        }

                        if (moved) {
                            playMoveSound();
                        }
                    }
                }
            }
        }
    }
}

void Game::playMoveSound() {
    moveSound.play();
}

void Game::update() {
    float deltaTime = deltaClock.restart().asSeconds();

    if (gameState == GameState::MENU) {
        menu.update();

        MenuState menuState = menu.getState();
        if (menuState == MenuState::PLAYING) {
            gameState = GameState::PLAYING;
            initializeGame();
            if (currentMap && currentMap->getPlayer()) {
                currentMap->getPlayer()->update(deltaTime);
            }
            showWinMessage = false;
            showGameOverMessage = false;
        }
        else if (menuState == MenuState::EXIT) {
            window.close();
        }
    }
    else if (gameState == GameState::PLAYING) {
        if (currentMap && currentMap->getPlayer()) {
            currentMap->getPlayer()->update(deltaTime);
        }

        // Kiểm tra Game Over
        if (currentMap && currentMap->getGameOver() && !showGameOverMessage) {
            showGameOverMessage = true;
            gameOverSound.play();
            backgroundMusic.stop();
            cout << "Game Over! Nhan R de choi lai hoac ESC de quay ve Menu." << endl;
        }

        // Kiểm tra Win
        if (currentMap && currentMap->checkWin() && !showWinMessage && !showGameOverMessage) {
            showWinMessage = true;
            winSound.play();
            backgroundMusic.stop();
            cout << "Chuc mung! Ban da chien thang!" << endl;
        }
    }
}

void Game::render() {
    window.clear();
    window.draw(backgroundSprite);

    if (gameState == GameState::MENU) {
        menu.draw(window);
    }
    else if (gameState == GameState::PLAYING) {
        if (currentMap) {
            currentMap->draw(window);

            // HIỂN THỊ GAME OVER
            if (showGameOverMessage) {
                sf::RectangleShape overlay(sf::Vector2f(800, 600));
                overlay.setFillColor(sf::Color(0, 0, 0, 180));
                window.draw(overlay);

                window.draw(gameOverSprite);

                sf::Font font;
                if (font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
                    sf::Text instruction;
                    instruction.setFont(font);
                    instruction.setString("Nhan R de choi lai | ESC de quay ve Menu");
                    instruction.setCharacterSize(18);
                    instruction.setFillColor(sf::Color::Red);
                    instruction.setPosition(270, 765);
                    window.draw(instruction);
                }
            }

            // HIỂN THỊ WIN
            if (showWinMessage) {
                sf::RectangleShape overlay(sf::Vector2f(800, 600));
                overlay.setFillColor(sf::Color(0, 0, 0, 150));
                window.draw(overlay);

                window.draw(winSprite);

                sf::Font font;
                if (font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
                    sf::Text instruction;
                    instruction.setFont(font);
                    instruction.setString("Nhan phim bat ky de quay ve Menu");
                    instruction.setCharacterSize(18);
                    instruction.setFillColor(sf::Color::Green);
                    instruction.setPosition(280,765);
                    window.draw(instruction);
                }
            }
        }
    }
    window.display();
}

void Game::initializeGame() {
    cleanupGame();

    int selectedMap = menu.getSelectedMap();
    if (selectedMap < 0) {
        selectedMap = 0;
    }

    std::string mapFileName = "map" + std::to_string(selectedMap + 1) + ".txt";
    std::cout << "Loading map: " << mapFileName << std::endl;

    currentMap = new Map(mapFileName, 32);
    std::cout << "Game initialized with " << mapFileName << "!" << std::endl;
}

void Game::cleanupGame() {
    if (currentMap) {
        delete currentMap;
        currentMap = nullptr;
    }
}