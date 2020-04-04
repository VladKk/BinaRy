#include <QMessageBox>
#include <QDebug>

#include "main_window.h"
#include "./ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        winNumParse(nullptr),
        winCharParse(nullptr),
        winArithmetic(nullptr),
        winLogic(nullptr),
        ui(new Ui::MainWindow) {
    setWindowIcon(QIcon(":/icons/windowIcon.ico"));

    ui->setupUi(this);

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
    auto *action = (QAction *) sender();

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
    auto *button = (QPushButton *) sender();

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

template<typename T>
T *MainWindow::getInstance(T *instance) {
    if (instance == nullptr)
        instance = new T(this);

    return instance;
}