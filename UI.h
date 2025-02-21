#ifndef UI_H
#define UI_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include "Board.h"

class UI : public QWidget {
    Q_OBJECT

public:
    explicit UI(QWidget* parent = nullptr);
    ~UI() override;
    void updateBoardUI();
private:
    QGridLayout* layout;
    Board* gameBoard;

    void setupBoard();
    void resetGame();
    void showWinMessage();
    void showLoseMessage();
    void updateButtonAppearance(int row, int col);  // Add this line

private slots:
    void onCellClicked(int row, int col);
    void onCellRightClicked(int row, int col);
};

#endif // UI_H
