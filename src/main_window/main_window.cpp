#include <QMessageBox>
#include <QDebug>

#include "main_window.h"
#include "./ui_main_window.h"

// Create main window with empty pointers on additional windows
MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        winNumParse(nullptr),
        winCharParse(nullptr),
        winArithmetic(nullptr),
        winLogic(nullptr),
        ui(new Ui::MainWindow) {
    // Set window icon and setup ui
    setWindowIcon(QIcon(":/icons/windowIcon.ico"));

    ui->setupUi(this);

    // Connect needed ui elements to actions
    connect(ui->actionAbout_developer, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionAbout_program, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(actions()));

    connect(ui->buttonLogic, SIGNAL(pressed()), this, SLOT(opsRedirect()));
    connect(ui->buttonArithmetic, SIGNAL(pressed()), this, SLOT(opsRedirect()));
    connect(ui->buttonNumParse, SIGNAL(pressed()), this, SLOT(opsRedirect()));
    connect(ui->buttonCharParse, SIGNAL(pressed()), this, SLOT(opsRedirect()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete winLogic;
    delete winArithmetic;
    delete winCharParse;
    delete winNumParse;
}

void MainWindow::actions() {
    // Receive signal from action
    auto *action = (QAction *) sender();

    // Trigger needed action
    if (action == ui->actionAbout_program) {
        QMessageBox::information(this, "BinaRy",
                                 "Simple program to operate with binary numbers\n"
                                 "May have a lot of bugs and mistakes\n"
                                 "Used technologies:\n"
                                 "C++, Qt, CMake");
    } else if (action == ui->actionAbout_developer) {
        QMessageBox::information(this, "BinaRy",
                                 "Find me in the Web!\n"
                                 "Telegram: @vlad_is_real\n"
                                 "GMail: vladislav.kolyadenko@gmail.com\n"
                                 "Instagram: @ncks_gwc");
    } else if (action == ui->actionExit)
        QApplication::quit();
    else {
        qDebug() << "Invalid action!" << Qt::endl;

        QApplication::exit(EXIT_FAILURE);
    }
}

void MainWindow::opsRedirect() {
    // Receive signal from button
    auto *button = (QPushButton *) sender();

    // Create new window object (only once) depending on button
    if (button == ui->buttonCharParse) {
        winCharParse = getInstance(winCharParse);

        winCharParse->show();
        this->hide();
    } else if (button == ui->buttonNumParse) {
        winNumParse = getInstance(winNumParse);

        winNumParse->show();
        this->hide();
    } else if (button == ui->buttonArithmetic) {
        winArithmetic = getInstance(winArithmetic);

        winArithmetic->show();
        this->hide();
    } else if (button == ui->buttonLogic) {
        winLogic = getInstance(winLogic);

        winLogic->show();
        this->hide();
    } else {
        qDebug() << "Invalid button!" << Qt::endl;

        QApplication::exit(EXIT_FAILURE);
    }
}

// "Singleton" for new windows
template<typename T>
T *MainWindow::getInstance(T *instance) {
    if (instance == nullptr)
        instance = new T(this);

    return instance;
}