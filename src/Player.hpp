#pragma once

#include <string>
#include "Board.hpp"

class Player {
protected:
    std::string token;
    int winCount;
    int tieCount;
    Board* board;
public:
    Player(Board* board, std::string token);
    virtual ~Player() {}
    virtual std::string info() = 0;
    int win();
    int tie();
    bool makeMove(int position);
    virtual int getPosition() = 0;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(Board* board, std::string token) : Player(board,token) {}
    int getPosition() override;
    std::string info() override;
    ~HumanPlayer() override;
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer(Board* board, std::string token) : Player(board,token) {}
    int getPosition() override;
    std::string info() override;
    ~ComputerPlayer() override;
};
