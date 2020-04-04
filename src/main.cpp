#include <QApplication>

#include "main_window/main_window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWin;

    mainWin.show();

    return QApplication::exec();
}
