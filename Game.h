// Game.h
#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <random>
#include <iostream>

// The Game class includes functionality to save and load game states, handle game events, and control the main game loop.
class Game {
public:
    Game(int maxInnings, bool attackFirst);
    void loadGame();
    void saveGame();
    void play();
private:
    // Game state variables
    int innings;
    int maxInnings;
    int strikes;
    int runs;
    bool isOver;
    bool attackFirst;
    // Random number generation related variables

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

    // Private member functions for internal game logic
    int getRandomEvent();
    void checkGameOver();
    void handleEvent(int event);
    int getValidInput();
    void performAttack();
    void performDefence();
};

#endif // GAME_H
