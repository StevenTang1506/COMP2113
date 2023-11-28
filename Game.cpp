#include "Game.h"
// Default constructor
Game::Game() 
    : innings(0), maxInnings(9), strikes(0), outs(0), runs(0), scores(0), 
      opponentScores(0), isOver(false), attackFirst(true), gen(rd()), dis(1, 100) 
{
    bases.fill(false);
}

// Constructor: Initializes a new game.
Game::Game(int maxInnings, bool attackFirst)
    : innings(0), maxInnings(maxInnings), strikes(0), outs(0), runs(0), 
      scores(0), opponentScores(0), isOver(false),
      attackFirst(attackFirst), gen(rd()), dis(0, 99) 
{
    bases.fill(false);
} // The initial game state is set, along with setting up the random number generator.

void mainMenu(Game& game);
// loadGame: Loads the game state from a file.
void Game::loadGame() {
    std::ifstream file("game_status.txt"); // Open the file
    if (file.is_open()) { // If the file is open, read the game state from it.
        file >> innings;
        file >> maxInnings;
        file >> strikes;
        file >> outs;
        file >> runs;
        file >> scores;
        file >> opponentScores;
        file >> isOver;
        file >> attackFirst;
        // Load the state of each base
        for (int i = 0; i < 3; ++i) {
            file >> bases[i];
        }
        file.close(); // Close the file after reading.
    }
    else {
        std::cout << "Unable to open the file. Please check if the file exists and try again.\n";
    }
}

// saveGame: Saves the current game state to a file.
void Game::saveGame() {
    std::ofstream file("game_status.txt"); // Open the file
    if (file.is_open()) { // If the file is open, write the game state to it.
        file << innings << "\n";
        file << maxInnings << "\n";
        file << strikes << "\n";
        file << outs << "\n";
        file << runs << "\n";
        file << scores << "\n";
        file << opponentScores << "\n";
        file << isOver << "\n";
        file << attackFirst << "\n";
        // Save the state of each base
        for (int i = 0; i < 3; ++i) {
            file << bases[i] << "\n";
        }
        file.close(); // Close the file after writing.
    }
    else {
        std::cout << "Unable to open the file. Please check the file permissions and try again.\n";
    }
}

void Game::showGameStatus() {
    std::cout << "------- Game Status -------" << '\n';
    std::cout << "Inning: " << innings << '\n';
    std::cout << "Outs: " << outs << '\n';
    std::cout << "Strikes: " << strikes << '\n';
    
    // Display the bases in a diamond pattern
    std::cout << "Bases:\n";
    std::cout << "   " << (bases[1] ? "2" : "◆") << "\n";
    std::cout << " ⟋   ⟍\n";
    std::cout << (bases[2] ? "3" : "◆") << "      " << (bases[0] ? "1" : "◆") << "\n";
    std::cout << " ⟍   ⟋\n";
    
    std::cout << "Your score: " << scores << '\n';
    std::cout << "Opponent's score: " << opponentScores << '\n';
    std::cout << "----------------------------" << '\n';
}

// getRandomEvent: Returns a random number between 0 and 99 inclusive.
int Game::getRandomEvent() {
    return dis(gen);
}

// checkGameOver: Checks if the game is over based on the number of innings played.
void Game::checkGameOver() {
    if (innings > maxInnings) {
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

// handleHit: Handle different no. of base hit.
void Game::handleHit(int basesToAdvance) {
    if (basesToAdvance == 4) { // Home run scenario
        runs += std::count(bases.begin(), bases.end(), true) + 1;
        std::fill(bases.begin(), bases.end(), false);
    } else { // All other scenarios
        for (int i = 2; i >= 0; --i) {
            if (bases[i]) {
                int newPosition = i + basesToAdvance;
                runs += (newPosition > 2);
                bases[i] = false;
                if (newPosition <= 2) bases[newPosition] = true;
            }
        }
        // Place the batter on base
        bases[basesToAdvance - 1] = true;
    }
}

// handleOutcome: Handles the outcome of the player's and computer's choices
void Game::handleOutcome(int diff, const std::array<int, 3>& eventOutcomes,  bool isAttack) {
    std::cout << "Result:" << "\n";
    std::string phase = isAttack ? "You're" : "opponent is";
    int event = getRandomEvent();
    if (diff == 0) {
        handleHit(4);
        strikes = 0;
        std::cout << "Homerun! " << phase << " earned 4 runs.\n";
    } else if (diff <= 2) {
        if (event < eventOutcomes[0]) {
            handleHit(2);
            std::cout << "2 bases hit! " << phase << " in scoring position.\n";
        } else if (event < eventOutcomes[1]) {
            handleHit(1);
            std::cout << "1 base hit! " << phase << " on base.\n";
        } else {
            strikes += 1;
            std::cout << "Strike!\n";
        }
    } else {
        strikes += 1;
        std::cout << "Strike!\n";
    }
    if (strikes >= 3) {
        outs += 1;
        strikes = 0;
        std::cout << "Three strikes! " << phase << " out!\n";
    }
}

// performAttack: Handles the attack phase of the game.
void Game::performAttack() {
    bases.fill(false);
    while (!isOver) {
        showGameStatus();
        std::cout << "Choose a number for batting (1-9): ";
        int playerChoice = getValidInput();
        int computerChoice = getRandomEvent() % 9 + 1;
        int diff = abs(playerChoice - computerChoice);
        std::array<int, 3> eventOutcomes = {50, 80};
        handleOutcome(diff, eventOutcomes);
        scores += runs;
        runs = 0;
        if (outs >= 3) {
            outs = 0;
            break;
        }
    }
}

// performDefence: Handles the defense phase of the game.
void Game::performDefence() {
    bases.fill(false);
    while (!isOver) {
        showGameStatus();
        std::cout << "Choose a number for pitching (1-9): ";
        int playerChoice = getValidInput();
        int computerChoice = getRandomEvent() % 9 + 1;
        int diff = abs(playerChoice - computerChoice);
        std::array<int, 3> eventOutcomes = {50, 80};
        handleOutcome(diff, eventOutcomes, false);
        opponentScores += runs;
        runs = 0;
        if (outs >= 3) {
            outs = 0;
            break;
        }
    }
}

// play: Main game loop.
void Game::play() {
    std::cout << "Welcome to the game!\n";
    
    while (!isOver) {
        std::string action;
        std::cout << "Enter 'menu' to access the main menu or 'continue' to proceed with the game.\n";
        std::cin >> action;

        // Check if user wants to access main menu
        if (action == "menu") {
            mainMenu(*this);
            if (getUserQuit()) {
                isOver = true;
            }
            continue;
        }

        if (attackFirst) {
            innings += 1;
            checkGameOver();
            performAttack();
            if (!isOver) {
                std::cout << "-------    Defence!    -------" << "\n";
                performDefence();
            }
        } else {
            innings += 1;
            checkGameOver();
            performDefence();
            if (!isOver) {
                std::cout << "-------    Attack!    -------" << "\n";
                performAttack();
            }
        }
    }
    std::cout << "Game over. Your final score: " << scores << ", Opponent's final score: " << opponentScores << "\n";
}
