#include "Cell.h"

// Constructor
// sets the initial start to the game
Cell::Cell() : mine(false), revealed(false), flag(false), numAdjMines(0), state(0) {}
//// Getters ////

//gets whether the cell is a mine
bool Cell::isMine() const {
    return mine;
}

//gets whether the cells has been revealed
bool Cell::isRevealed() const {
    return revealed;
}

//gets whether the cell has been flagged or not
bool Cell::isFlag() const {
    return state ==1;
}

//returns true if it is a question (the state is set to 2)
bool Cell::isQuestion() const {
    return state ==2;
}

//returns the current state
int Cell::getState() const{
    return state;
}

//gets the number of mines adjacent to the cell
int Cell::getAdjMines() const {
    return numAdjMines;
}

//// Setters ////

//sets the cell to contiain a mine (T/F)
void Cell::setMine(bool newMine) {
    mine = newMine;
}

//sets whether the cell has been revealed
void Cell::setRevealed(bool newRevealed) {
    revealed = newRevealed;
}

//sets whether the flag is set
void Cell::setFlag(bool newFlag) {
    flag = newFlag;
}

//sets whether the flag is set
void Cell::setQuestion(bool newQuestion) {
    question = newQuestion;
}

//sets the number of adjacent mines to the current cell
void Cell::setAdjMines(int count) {
    numAdjMines = count;
}

//Changes the state of the current cell
void Cell::changeState() {
        state = (state + 1) % 3;
}
