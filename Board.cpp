#include "Board.h"
#include <random>
#include <algorithm>

int Board::clickCount = 0; //initially sets i to be 0

//Initializes the grid to and sets the number of cells remaining
Board::Board() 
    : gameOver(false), gameWon(false), remainingCells(ROWS * COLS - MINES) {
    grid.resize(ROWS, std::vector<Cell>(COLS));
}

//starts the game, mainly call other cells to initialize the board correctly
void Board::startGame() {
    resetGame();
    placeMines();
    calculateAdjacentMines();
}

//goes through each row and cell then resets it to a new cell object
void Board::resetGame() {
    for (auto& row : grid) {
        for (auto& cell : row) {
            cell = Cell();
        }
    }
    gameOver = false;
    gameWon = false;
    remainingCells = ROWS * COLS - MINES;
}

// places the mines randomly throughout the field, tripple randomizes if a cell is a mine
void Board::placeMines() {
    std::vector<int> positions(ROWS * COLS); //makes vector grid
    std::iota(positions.begin(), positions.end(), 0); //sequentially goes through from start to end
    std::random_device rd; //non-predictable number generator
    std::mt19937 g(rd()); //very efficent random number generator
    std::shuffle(positions.begin(), positions.end(), g); //shuffles the random numbers

	//goes though the  grid and places the mines
    for (int i = 0; i < MINES; ++i) {
        int pos = positions[i];
        int row = pos / COLS;
        int col = pos % COLS;
        grid[row][col].setMine(true);
    }
}

//calculates the number of adjacent mines
void Board::calculateAdjacentMines() {

    //loop through the board
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {

            //make sure the current spot is not a mine
            if (!grid[row][col].isMine()) {
                int count = 0; //make a counter

                //loop through surrounding
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {

                        //adds together the surrounding mines
                        if (isValidPosition(row + dr, col + dc) && grid[row + dr][col + dc].isMine()) {
                            ++count;
                        }
                    }
                }
                grid[row][col].setAdjMines(count); //sets the number of the cell
            }
        }
    }
}

//reveals the cell
void Board::revealCell(int row, int col) {
    if (!isValidPosition(row, col) || grid[row][col].isRevealed() || grid[row][col].isFlag() || grid[row][col].isQuestion()) {
        return;
    }

    grid[row][col].setRevealed(true);
    --remainingCells; //subtract the number needed (how many non mine nodes need to be uncovered before winning)

    //selected node is a mine
    if (grid[row][col].isMine()) {
        gameOver = true;
    } 

    //if there are no mines around it, reveal those cells too
    else if (grid[row][col].getAdjMines() == 0) {
        revealAdjacentEmptyCells(row, col);
    }

    // If there are no cells without mines, you win
    if (remainingCells == 0) {
        gameWon = true;
        gameOver = true;
    }
}

//reveals adjacent cells if they are empty too
void Board::revealAdjacentEmptyCells(int row, int col) {

    //goes through each node around the cell
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            int newRow = row + dr;
            int newCol = col + dc;

            //makes sure the cell is valid to uncover
            if (isValidPosition(newRow, newCol) && !grid[newRow][newCol].isRevealed() && !grid[newRow][newCol].isFlag()) {
                grid[newRow][newCol].setRevealed(true); //reveal that cell
                --remainingCells; //subtract it from the num spaces without mines left

                //recursive call, it its neighbors are empty, reveal them too
                if (grid[newRow][newCol].getAdjMines() == 0) {
                    revealAdjacentEmptyCells(newRow, newCol);
                }
            }
        }
    }
}

//go through the different marked types 1. flag 2. question 0. nothing
void Board::changeMarkCell(int row, int col) {
   if (!isValidPosition(row, col) || isRevealed(row, col)) {
        return;
   }
        grid[row][col].changeState();
    }

//Game Won condition
bool Board::isGameWon() const {
    return gameWon;
}

//Game lost condition
bool Board::isGameOver() const {
    return gameOver;
}

//// Most of this stuff is just to make sure the position is valid ////


//checks if the current cell is a mine
bool Board::isMine(int row, int col) const {
    return isValidPosition(row, col) && grid[row][col].isMine();
}

//checks f the current spot has been revealed
bool Board::isRevealed(int row, int col) const {
    return isValidPosition(row, col) && grid[row][col].isRevealed();
}

//gets the number of  mines, if there are none return 0
int Board::getAdjacentMines(int row, int col) const {
    return isValidPosition(row, col) ? grid[row][col].getAdjMines() : 0;
}

//checks if the current spot is flagged
bool Board::isFlagged(int row, int col) const {
    return isValidPosition(row, col) && grid[row][col].isFlag();
}

//checks if the current spot is a question mark
bool Board::isQuestion(int row, int col) const {
    return isValidPosition(row, col) && grid[row][col].isQuestion();
}

//checks if the current cell is in a valid spot within the board
bool Board::isValidPosition(int row, int col) const {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

//gets the current cells state
int Board::getCellState(int row, int col) const {
    if (isValidPosition(row, col)) {
        return grid[row][col].getState();
    }

    return -1;
}
