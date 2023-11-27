#include "Game.h"

int main() {
    // Prompt the user to input the maximum number of innings
    int maxInnings;
    std::cout << "Enter the maximum number of innings: ";
    while (!(std::cin >> maxInnings) || maxInnings <= 0) {
        std::cout << "Invalid input. Please enter a positive number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Prompt the user to choose whether they want to attack first
    bool attackFirst;
    std::string response;
    std::cout << "Do you want to attack first? (yes/no): ";
    std::cin >> response;
    
    // Check the response
    if (response == "yes" || response == "Yes" || response == "YES") {
        attackFirst = true;
    } else if (response == "no" || response == "No" || response == "NO") {
        attackFirst = false;
    } else {
        std::cout << "Invalid input. Defaulting to attacking first.\n";
        attackFirst = true;
    }

    // Create a Game object with the user's input
    Game game(maxInnings, attackFirst);

    // Play the game
    game.play();

    return 0;
}
