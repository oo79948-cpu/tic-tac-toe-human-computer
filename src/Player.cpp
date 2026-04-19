#include "Player.hpp"

#include <iostream>
#include <ostream>
#include <limits>

Player::Player(Board* board, std::string token) {
    this->board = board;
    this->token = token;
    winCount = 0;
    tieCount = 0;
}

bool Player::makeMove(int position) {
    return board->makeMove(position, token);
}

int Player::win() {
    winCount++;
    return winCount;
}

int Player::tie() {
    tieCount++;
    return tieCount;
}

int HumanPlayer::getPosition() {
    int userInput;
    std::cin >> userInput;
    if (std::cin.fail()) {
        userInput = -1;
    }
    std::cin.clear(); // Clear the error flag
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
    return userInput;
}

std::string HumanPlayer::info() {
    return "Player " + token + " (Human)";
}

HumanPlayer::~HumanPlayer() {
    std::cout << info() << " - # of wins: " << winCount << ", # of ties:  " << tieCount << std::endl;
    std::cout << "Goodbye!"  << std::endl;
}

int ComputerPlayer::getPosition() {
    int position = board->getFirstAvailablePosition();
    std::cout << "\nI'm picking first available position: " << position << std::endl;
    return position;
}

std::string ComputerPlayer::info() {
    return "Player " + token + " (Computer)";
}

ComputerPlayer::~ComputerPlayer() {
    std::cout << info() << " - # of wins: " << winCount << ", # of ties:  " << tieCount << std::endl;
    std::cout << "Goodbye!"  << std::endl;
}
