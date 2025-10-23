#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include "Menu.h"
#include "Map.h"

enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class Game {
private:
    sf::RenderWindow window;
    Menu menu;
    Map* currentMap;
    GameState gameState;
    sf::Music backgroundMusic;
    sf::SoundBuffer moveSoundBuffer;
    sf::Sound moveSound;
    sf::SoundBuffer winSoundBuffer;
    sf::Sound winSound;
    sf::SoundBuffer gameOverSoundBuffer; // Game Over sound
    sf::Sound gameOverSound;

    sf::Texture winTexture;
    sf::Sprite winSprite;
    sf::Texture gameOverTexture; // Game Over texture
    sf::Sprite gameOverSprite;

    bool showWinMessage;
    bool showGameOverMessage; // Game Over message flag

    sf::Clock deltaClock;

public:
    Game();
    ~Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void initializeGame();
    void cleanupGame();
    void playMoveSound();
};