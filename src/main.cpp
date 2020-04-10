#include <QApplication>

#include "main_window/main_window.h"

int main(int argc, char *argv[]) {
    // Create Qt application object
    QApplication app(argc, argv);

    // Deny quit after closing window (for additional actions)
    QApplication::setQuitOnLastWindowClosed(false);

    // Create and show main window
    MainWindow mainWin;

    mainWin.show();

    return QApplication::exec();
}
