// Game.h
#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <random>
#include <iostream>

class Game {
public:
    Game(int maxInnings, bool attackFirst);
    void loadGame();
    void saveGame();
    void gameLoop();
private:
    int innings;
    int maxInnings;
    int strikes;
    int runs;
    bool isOver;
    bool attackFirst;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
    int getRandomEvent();
    void checkGameOver();
    void handleEvent(int event);
    int getValidInput();
    void performAttack();
    void performDefence();
};

#endif // GAME_H