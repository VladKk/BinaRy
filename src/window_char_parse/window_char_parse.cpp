#include <QMessageBox>
#include <QDebug>

#include "window_char_parse.h"
#include "./ui_window_char_parse.h"

WindowCharParse::WindowCharParse(QWidget *parent) :
        QMainWindow(parent),
        binRegExpVal(new QRegExpValidator(QRegExp("[01]{0,}"), this)),
        ui(new Ui::WindowCharParse) {
    setWindowIcon(QIcon(":/icons/windowIcon.ico"));

    ui->setupUi(this);

    ui->buttonSwap->setIcon(QIcon(":/icons/swapIcon.ico"));

    connect(ui->actionAbout_developer, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionAbout_program, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionRefresh, SIGNAL(triggered()), this, SLOT(actions()));

    connect(ui->buttonBack, SIGNAL(pressed()), this, SLOT(back()));

    connect(ui->buttonSwap, SIGNAL(pressed()), this, SLOT(swap()));

    connect(ui->buttonTranslate, SIGNAL(pressed()), this, SLOT(parse()));
}

WindowCharParse::~WindowCharParse() {
    delete ui;
    delete binRegExpVal;
}

void WindowCharParse::actions() {
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
    } else if (action == ui->actionRefresh) {
        ui->lineEditUpper->clear();
        ui->lineEditLower->clear();
    } else if (action == ui->actionExit)
        QApplication::quit();
    else {
        qDebug() << "Invalid action!" << Qt::endl;

        QApplication::exit(EXIT_FAILURE);
    }
}

void WindowCharParse::back() {
    QMainWindow::parentWidget()->show();

    this->hide();
}

void WindowCharParse::swap() {
    QString temp = ui->lineEditLower->text();
    ui->lineEditLower->setText(ui->lineEditUpper->text());
    ui->lineEditUpper->setText(temp);

    if (ui->lineEditUpper->placeholderText() == "Enter text here") {
        ui->lineEditUpper->setPlaceholderText("Enter binary code here");
        ui->lineEditUpper->setValidator(binRegExpVal);
    } else
        ui->lineEditUpper->setPlaceholderText("Enter text here");

    ui->lineEditLower->clear();
}

void WindowCharParse::parse() {
    if (ui->lineEditUpper->text().isEmpty())
        ui->statusBar->showMessage("Line edit shouldn`t be empty", 5000);
}