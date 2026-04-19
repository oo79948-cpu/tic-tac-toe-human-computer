#include "tictactoe.hpp"

#include <iostream>
#include <string>
#include <limits>

#include "Board.hpp"

Game::Game() {
    std::cout << "Welcome to Tic-Tac-Toe!" << std::endl;
    initGame();
}

void Game::restartGame() {
    delete playerX;
    delete playerO;
    initGame();
}

void Game::initGame() {
    std::cout << "\nWhat kind of game would you like to play?" << std::endl;
    std::cout << "1. Human vs. Human" << std::endl;
    std::cout << "2. Human vs. Computer" << std::endl;
    std::cout << "3. Computer vs. Human" << std::endl;
    int option = -1;
    bool isOptionValid = false;
    do {
        std::cout << "\nWhat is your selection? ";
        option = getPlayerOption();
        isOptionValid = option == 1 || option == 2 || option == 3;
        if (!isOptionValid) {
            std::cout << "Invalid option!" << std::endl;
        }
    } while (!isOptionValid) ;

    if (option == 1) {
        playerX = new HumanPlayer(&board,"X");
        playerO = new HumanPlayer(&board,"O");
    } else if (option == 2) {
        playerX = new HumanPlayer(&board,"X");
        playerO = new ComputerPlayer(&board,"O");
    }
    else if (option == 3) {
        playerX = new ComputerPlayer(&board,"X");
        playerO = new HumanPlayer(&board,"O");
    }
    currentPlayer = playerX;
    winner = nullptr;
    std::cout << "Great! " << currentPlayer->info() << " goes first." << std::endl;
}

int Game::getPlayerOption() {
    int userInput;
    std::cin >> userInput;
    if (std::cin.fail()) {
        userInput = -1;
    }
    std::cin.clear(); // Clear the error flag
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
    return userInput;
}

Game::~Game() {
    std::cout << "Goodbye Players!" << std::endl;
    delete playerX;
    delete playerO;
}

void Game::changePlayer() {
    if (currentPlayer == playerX) {
        currentPlayer = playerO;
    } else {
        currentPlayer = playerX;
    }
}

bool Game::keepPlaying() {
    return !gameEnded() || getPlayAgain();
}

bool Game::gameEnded() {
    if (winner != nullptr) {
        board.printBoard();
        std::cout << std::endl << winner->info() << " wins!" << std::endl;
        winner->win();
        currentPlayer = winner;
        winner = nullptr;
        changePlayer(); // loser starts next game
        return true;
    }
    if (board.isBoardFull()) {
        std::cout << std::endl << "Tie!!!" << std::endl;
        playerO->tie();
        playerX->tie();
        return true;
    }
    return false;
}

bool Game::getPlayAgain() {
    while (true) {
        std::string response;
        std::cout << "Play again? (yes or no): ";
        std::cin >> response;
        if (response == "yes") {
            board.initBoard();
            std::cout << "Do you want to change the game mode? (respond yes if you accept): ";
            std::cin >> response;
            if (response == "yes") {
                restartGame();
            }
            return true;
        }
        if (response == "no") {
            return false;
        }
        std::cout << "That is not a valid entry!" << std::endl;
    }
}

bool Game::weHaveAWinner() {
    return board.isGameWon();
}


void Game::playGame() {
    do {
        board.printBoard();
        std::cout << std::endl << currentPlayer->info() << ", what is your move? ";
        int position = currentPlayer->getPosition();
        if (!currentPlayer->makeMove(position)) {
            std::cout << "That is not a valid move! Try again." << std::endl;
        } else {
            if (weHaveAWinner()) {
                winner = currentPlayer;
            }
            changePlayer();
        }
    } while (keepPlaying());
}
