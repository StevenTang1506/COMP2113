// Game.h
#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <random>
#include <iostream>

// The Game class includes functionality to save and load game states, handle game events, and control the main game loop.
class Game {
    bool userQuit;
public:
    Game(); // Default constructor
    Game(int maxInnings, bool attackFirst);
    void loadGame();
    void saveGame();
    void play();
    void setMaxInnings(int maxInnings) { this->maxInnings = maxInnings; } // Setter for maxInnings
    void setAttackFirst(bool attackFirst) { this->attackFirst = attackFirst; } // Setter for attackFirst
    void setUserQuit(bool quit) {
        userQuit = quit;
    }
    bool getUserQuit() const {
        return userQuit;
    }

private:
    // Game state variables
    int innings;
    int maxInnings;
    int strikes;
    int outs;
    int runs;
    int scores;
    int opponentScores;
    bool isOver;
    bool attackFirst;
    std::array<bool, 3> bases;
    
    // Random number generation related variables
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

    // Private member functions for internal game logic
    int getRandomEvent();
    void checkGameOver();
    void handleEvent(int event);
    int getValidInput();
    void handleOutcome(int diff, const std::array<int, 3>& eventOutcomes,  bool isAttack = true);
    void performAttack();
    void performDefence();
    void showGameStatus();
    void handleHit(int basesToAdvance);
};

void mainMenu(Game& game);

#endif // GAME_H
