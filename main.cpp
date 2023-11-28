#include "Game.h"

void mainMenu(Game& game, bool loaded = false) {
    int maxInnings;
    bool attackFirst;
    while (true) {
        std::cout << "1. Play Game\n";
        std::cout << "2. Settings\n";
        std::cout << "Choose an option: ";

        int option;
        std::cin >> option;
        std::string response;

        switch (option) {
            case 1: // Play the game
                // Prompt the user to input the maximum number of innings
                if (!loaded) {
                
                    std::cout << "Enter the maximum number of innings: ";
                    // Handle invalid input
                    while (!(std::cin >> maxInnings) || maxInnings <= 0) {
                        std::cout << "Invalid input. Please enter a positive number: ";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    
                        // Prompt the user to choose whether they want to attack first
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
                        // Update the Game object with the user's input
                        game.setMaxInnings(maxInnings);
                        game.setAttackFirst(attackFirst);
                }
                game.play();
                break;

            case 2: // Access settings
                while (true) {
                    std::cout << "\nSettings:\n";
                    std::cout << "1. Save Game\n";
                    std::cout << "2. Load Game\n";
                    std::cout << "3. Back to Main Menu\n";
                    std::cout << "4. Quit Game\n";
                    std::cout << "Choose an option: ";

                    int settingsOption;
                    std::cin >> settingsOption;
                    
                    switch (settingsOption) {
                        case 1: // Save the game
                            game.saveGame();
                            std::cout << "Game saved successfully.\n";
                            break;
                        case 2: // Load the game
                            if (game.loadGame()) {
                                game.setLoaded(true);
                            } else {
                                game.setLoaded(false);
                                break;
                            }
                            std::cout << "Game loaded successfully.\n";
                            break;
                        case 3: // Back to main menu
                            return;
                        case 4: // Quit the game
                            std::cout << "Quitting the game...\n";
                            game.setUserQuit(true);
                            return;
                        default:
                            std::cout << "Invalid option. Please try again.\n";
                    }
                }
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }
}

int main() {
    // Create a Game object with default values
    Game game;

    // Call the main menu
    mainMenu(game, false);

    if (game.getUserQuit()) {
        std::cout << "Thank you for playing. See you next time!\n";
    } else {
        mainMenu(game, game.getLoaded());
    }

    return 0;
}
