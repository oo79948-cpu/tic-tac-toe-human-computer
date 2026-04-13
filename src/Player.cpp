#include "Player.hpp"

#include <iostream>
#include <ostream>
#include <limits>

Player::Player(Board* board, std::string token) {
    this->board = board;
    this->token = token;
    winCount = 0;
    tieCount = 0;
    isComputer = false;
}

void Player::setIsComputer(bool isComputer) {
    this->isComputer = isComputer;
}

int Player::getPositionHuman() {
    int userInput;
    std::cin >> userInput;
    if (std::cin.fail()) {
        userInput = -1;
    }
    std::cin.clear(); // Clear the error flag
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
    return userInput;
}
int Player::getPositionComputer() {
    int position = board->getFirstAvailablePosition();
    std::cout << "\nI'm picking first available position: " << position << std::endl;
    return position;
}

int Player::getPosition() {
    return isComputer ? getPositionComputer() : getPositionHuman();
}

bool Player::makeMove(int position) {
    return board->makeMove(position, token);
}

std::string Player::info() {
    if (isComputer) {
        return "Player " + token + " (Computer)";
    }
    return "Player " + token + " (Human)";
}

int Player::win() {
    winCount++;
    return winCount;
}

int Player::tie() {
    tieCount++;
    return tieCount;
}


Player::~Player() {
    std::cout << info() << " - # of wins: " << winCount << ", # of ties:  " << tieCount << std::endl;
    std::cout << "Goodbye!"  << std::endl;
}