#pragma once
#include <vector>
#include <string>

class Board {
    std::vector<std::string> grid;
    int trapCellPosition = -1;
public:
    Board();
    void initBoard();
    bool canMakeMove(int position);
    bool makeMove(int position, std::string token);
    void printBoard();
    bool isGameWon();
    bool isBoardFull();
    int getFirstAvailablePosition();
    void setTrap();
    bool isTrap(int position);
    void resetTrap();
};