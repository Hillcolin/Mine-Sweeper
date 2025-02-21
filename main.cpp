#include <QApplication>
#include "UI.h"

//Runs the qt app
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    UI w;
    w.show();
    return a.exec();
}
