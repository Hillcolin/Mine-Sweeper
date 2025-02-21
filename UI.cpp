#include "UI.h"
#include <QMessageBox>
#include <QVBoxLayout>

//initializes the board
UI::UI(QWidget* parent)
    : QWidget(parent), gameBoard(new Board())
{
    //makes it into a grid layout
    layout = new QGridLayout(this);
    setLayout(layout);


    setupBoard();
}

//cleanup for when a object is deleted
UI::~UI()
{
    delete gameBoard;
}

// starts the game, sets up the button grid, adds left and right click connections
void UI::setupBoard()
{
    //starts the game
    gameBoard->startGame();

    //Sets up the button grid
    for (int row = 0; row < gameBoard->getRows(); ++row) {
        for (int col = 0; col < gameBoard->getCols(); ++col) {
            QPushButton* button = new QPushButton(this); //add button
            button->setFixedSize(30, 30); //set button size
            layout->addWidget(button, row, col); 

            //Connect the left click ability
            connect(button, &QPushButton::clicked, [this, row, col]() {
                onCellClicked(row, col);
            });

            //Connect the right click ability
            button->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(button, &QPushButton::customContextMenuRequested, [this, row, col]() {
                onCellRightClicked(row, col);
            });
        }
    }
}

//Called for when a cell is left clicked
void UI::onCellClicked(int row, int col)
{
    if (gameBoard->isGameOver()) return; //makes sure the game is not over

    gameBoard->revealCell(row, col); //reveals cell clicked
    updateBoardUI(); //updates it

    //checks game win/lose condition
    if (gameBoard->isGameOver()) {
        if (gameBoard->isGameWon()) {
            showWinMessage();
        } 
        else {
            showLoseMessage();
        }
    }
}

//Celled for when a cell is right clicked
void UI::onCellRightClicked(int row, int col)
{
    if (gameBoard->isGameOver()) return;  //makes sure the game is not over

    //sets the type on the cell
    gameBoard->changeMarkCell(row,col);

    updateButtonAppearance(row, col); //calls method to set the appearance if the cell 
}


//Updates the board with new changes
void UI::updateBoardUI()
{
    //loops through everything
    for (int row = 0; row < gameBoard->getRows(); ++row) {
        for (int col = 0; col < gameBoard->getCols(); ++col) {
            updateButtonAppearance(row, col);//updates the appearance of each cell
        }
    }
}

//updates the apprearance of the button
void UI::updateButtonAppearance(int row, int col)
{
    //gets certan position in grid and its widget, then casts it to a QPushButton
    QPushButton* button = qobject_cast<QPushButton*>(layout->itemAtPosition(row, col)->widget()); 

    if (!button) return;// if its not a button we dont want it

    
    if (gameBoard->isRevealed(row, col)) {
        //if the the cell is left clicked and is a mine, get the image to a mine
        if (gameBoard->isMine(row, col)) {
            button->setIcon(QIcon("icons/mine.png"));
        }

        //gets the number of adjacent mines and sets the text of the current cell to that. (Empty str if no mines)
        else {
            int adjacentMines = gameBoard->getAdjacentMines(row, col);

            if (adjacentMines > 0) {
                button->setText(QString::number(adjacentMines));
            } 
            else {
                button->setText("");
            }
            button->setFlat(true);//keeps the button pressed in to give it the appearance of used
        }
    }
    else {

        switch(gameBoard->getCellState(row, col)) {

            case 0: //sets the icon to empty
                button->setIcon(QIcon());
                button->setText("");
                button->setFlat(false);
                break;

            case 1: //sets the icon to a flag
                button->setIcon(QIcon("icons/flag.png"));
                button->setIconSize(QSize(20, 20));
                break;

            case 2: //sets the icon to a question mark
                button->setIcon(QIcon("icons/question.png"));
                button->setIconSize(QSize(20, 20));
                break;
        }
}
}
//starts the game over
void UI::resetGame()
{
    gameBoard->startGame();
    updateBoardUI();
}

// shows win popup, then resets the game
void UI::showWinMessage()
{
    QMessageBox::information(this, "Congratulations!", "You Win!");
    resetGame();
}

// shows lose popup, then resets the game
void UI::showLoseMessage()
{
    QMessageBox::information(this, "Game Over", "You've hit a mine! Game over.");
    resetGame();
}
