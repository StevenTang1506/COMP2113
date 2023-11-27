#include "Game.h"

// Constructor: Initializes a new game.
Game::Game(int maxInnings, bool attackFirst)
    : innings(0), maxInnings(maxInnings), strikes(0), runs(0), isOver(false),
      attackFirst(attackFirst), gen(rd()), dis(0, 99) {} // The initial game state is set, along with setting up the random number generator.

// loadGame: Loads the game state from a file.
void Game::loadGame() {
    std::ifstream file("game_status.txt"); // Open the file
    if (file.is_open()) { // If the file is open, read the game state from it.
        file >> innings;
        file >> maxInnings;
        file >> strikes;
        file >> runs;
        file >> isOver;
        file >> attackFirst;
        file.close(); // Close the file after reading.
    }
}

// saveGame: Saves the current game state to a file.
void Game::saveGame() {
    std::ofstream file("game_status.txt"); // Open the file
    if (file.is_open()) { // If the file is open, write the game state to it.
        file << innings << "\n";
        file << maxInnings << "\n";
        file << strikes << "\n";
        file << runs << "\n";
        file << isOver << "\n";
        file << attackFirst << "\n";
        file.close(); // Close the file after writing.
    }
}

// getRandomEvent: Returns a random number between 0 and 99 inclusive.
int Game::getRandomEvent() {
    return dis(gen);
}

// checkGameOver: Checks if the game is over based on the number of innings played.
void Game::checkGameOver() {
    if (innings >= maxInnings) {
        isOver = true;
    }
}

// getValidInput: Asks the user for a number between 1 and 9, and keeps asking until a valid number is entered.
int Game::getValidInput() {
    int input;
    while (!(std::cin >> input) || input < 1 || input > 9) {
        std::cout << "Invalid input. Please enter a number between 1 and 9: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return input;
}

// performAttack: Handles the attack phase of the game. The player and computer choose numbers and the result is determined based on the difference.
void Game::performAttack() {
    // player chooses a number
    std::cout << "Choose a number for batting (1-9): ";
    int playerChoice = getValidInput();

    // computer chooses a number
    int computerChoice = getRandomEvent() % 9 + 1;

    // check the result
    int diff = abs(playerChoice - computerChoice);
    if (diff == 0) {
        // homerun
        runs += 4;
        std::cout << "Homerun! You earned 4 runs.\n";
    } else if (diff == 1) {
        // 70% 2 bases, 20% 1 base, 10% out
        int event = getRandomEvent();
        if (event < 70) {
            runs += 2;
            std::cout << "2 bases hit! You earned 2 runs.\n";
        } else if (event < 90) {
            runs += 1;
            std::cout << "1 base hit! You earned 1 run.\n";
        } else {
            strikes += 1;
            std::cout << "Out!\n";
        }
    } else if (diff == 2) {
        // 70% 1 base, 20% out, 10% strike
        int event = getRandomEvent();
        if (event < 70) {
            runs += 1;
            std::cout << "1 base hit! You earned 1 run.\n";
        } else if (event < 90) {
            strikes += 1;
            std::cout << "Out!\n";
        } else {
            strikes += 1;
            std::cout << "Strike!\n";
        }
    } else {
        // 80% out, 20% strike
        int event = getRandomEvent();
        if (event < 80) {
            strikes += 1;
            std::cout << "Out!\n";
        } else {
            strikes += 1;
            std::cout << "Strike!\n";
        }
    }

    // check if the inning is over
    if (strikes >= 3) {
        strikes = 0;
        innings += 1;
        checkGameOver();
    }
}

// performDefence: Handles the defense phase of the game. The player and computer choose numbers and the result is determined based on the difference.
void Game::performDefence() {
    // player chooses a number
    std::cout << "Choose a number for pitching (1-9): ";
    int playerChoice = getValidInput();

    // computer chooses a number
    int computerChoice = getRandomEvent() % 9 + 1;

    // check the result
    int diff = abs(playerChoice - computerChoice);
    if (diff == 0) {
        // strike
        strikes += 1;
        std::cout << "Strike!\n";
    } else if (diff == 1) {
        // 70% out, 20% 1 base, 10% 2 bases
        int event = getRandomEvent();
        if (event < 70) {
            strikes += 1;
            std::cout << "Out!\n";
        } else if (event < 90) {
            runs -= 1;
            std::cout << "1 base hit by opponent. You lost 1 run.\n";
        } else {
            runs -= 2;
            std::cout << "2 bases hit by opponent. You lost 2 runs.\n";
        }
    } else if (diff == 2) {
        // 70% 1 base, 20% 2 bases, 10% homerun
        int event = getRandomEvent();
        if (event < 70) {
            runs -= 1;
            std::cout << "1 base hit by opponent. You lost 1 run.\n";
        } else if (event < 90) {
            runs -= 2;
            std::cout << "2 bases hit by opponent. You lost 2 runs.\n";
        } else {
            runs -= 4;
            std::cout << "Homerun by opponent! You lost 4 runs.\n";
        }
    } else {
        // 80% 2 bases, 20% homerun
        int event = getRandomEvent();
        if (event < 80) {
            runs -= 2;
            std::cout << "2 bases hit by opponent. You lost 2 runs.\n";
        } else {
            runs -= 4;
            std::cout << "Homerun by opponent! You lost 4 runs.\n";
        }
    }

    // check if the inning is over
    if (strikes >= 3) {
        strikes = 0;
        innings += 1;
        checkGameOver();
    }
}

// play: Main game loop. Alternates between attack and defense phases until the game is over.
void Game::play() {
    std::cout << "Welcome to the game!\n";
    while (!isOver) {
        if (attackFirst) {
            performAttack();
            if (!isOver) {
                performDefence();
            }
        } else {
            performDefence();
            if (!isOver) {
                performAttack();
            }
        }
    }
    std::cout << "Game over. Final score: " << runs << "\n";
}
