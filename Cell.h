#ifndef CELL_H
#define CELL_H

class Cell {
public:
    explicit Cell();  // Constructor

    // Getters
    bool isMine() const;
    bool isRevealed() const;
    bool isFlag() const;
    bool isQuestion() const;
    int getAdjMines() const;
    int getState() const;

    // Setters
    void setMine(bool newMine);
    void setRevealed(bool newRevealed);
    void setFlag(bool newFlag);
    void setQuestion(bool newQuestion);
    void setAdjMines(int count);

    void changeState();
private:
    bool mine;       // True if the cell contains a mine
    bool revealed;   // True if the cell has been revealed
    bool flag;       // True if the cell is flagged
    bool question;   // true if the cell is question marked
    int numAdjMines; // Number of adjacent mines
    int state;
};

#endif // CELL_H
