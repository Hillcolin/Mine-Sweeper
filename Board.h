#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Cell.h"

class Board {
public:
    Board();
    void startGame();
    void revealCell(int row, int col);
    bool isGameWon() const;
    bool isGameOver() const;
    bool isMine(int row, int col) const;
    bool isRevealed(int row, int col) const;
    int getAdjacentMines(int row, int col) const;
    bool isFlagged(int row, int col) const;
    bool isQuestion(int row, int col) const;
    int getRows() const { return ROWS; }
    int getCols() const { return COLS; }
    void changeMarkCell(int row, int col);
    int getCellState(int row, int col) const;

private:
    static const int ROWS = 16;
    static const int COLS = 30;
    static const int MINES = 99;
    static int clickCount;
    
    bool gameOver;
    bool gameWon;
    int remainingCells;
    std::vector<std::vector<Cell>> grid;

    void resetGame();
    void placeMines();
    void calculateAdjacentMines();
    bool isValidPosition(int row, int col) const;
    void revealAdjacentEmptyCells(int row, int col);
};

#endif
