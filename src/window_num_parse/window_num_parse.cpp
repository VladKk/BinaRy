#include <QMessageBox>
#include <QDebug>

#include "window_num_parse.h"
#include "./ui_window_num_parse.h"

WindowNumParse::WindowNumParse(QWidget *parent) :
        QMainWindow(parent),
        binValidator(new QRegExpValidator(QRegExp("[01]{0,}"), this)),
        decValidator(new QRegExpValidator(QRegExp("[0-9]{0,}"), this)),
        octValidator(new QRegExpValidator(QRegExp("[0-8]{0,}"), this)),
        hexValidator(new QRegExpValidator(QRegExp("[0-9A-F]{0,}"), this)),
        ui(new Ui::WindowNumParse) {
    setWindowIcon(QIcon(":/icons/windowIcon.ico"));

    ui->setupUi(this);

    ui->buttonSwap->setIcon(QIcon(":/icons/swapIcon.ico"));

    connect(ui->actionAbout_developer, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionAbout_program, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionRefresh, SIGNAL(triggered()), this, SLOT(actions()));

    connect(ui->comboBoxFrom, SIGNAL(currentIndexChanged(int)), this, SLOT(switchValidators()));

    connect(ui->buttonBack, SIGNAL(pressed()), this, SLOT(back()));

    connect(ui->buttonSwap, SIGNAL(pressed()), this, SLOT(swap()));
}

WindowNumParse::~WindowNumParse() {
    delete ui;
    delete binValidator;
    delete decValidator;
    delete octValidator;
    delete hexValidator;
}

void WindowNumParse::actions() {
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
        ui->lineEditNum->clear();
        ui->comboBoxFrom->setCurrentIndex(0);
        ui->comboBoxTo->setCurrentIndex(0);
        ui->labelResult->setText("Result:");
    } else if (action == ui->actionExit)
        QApplication::quit();
    else {
        qDebug() << "Invalid action!" << Qt::endl;

        QApplication::exit(EXIT_FAILURE);
    }
}

void WindowNumParse::back() {
    QMainWindow::parentWidget()->show();

    this->hide();
}

void WindowNumParse::swap() {
    QString temp = ui->labelResult->text().mid(
            ui->labelResult->text().indexOf(' ') + 1,
            ui->labelResult->text().size() -
            ui->labelResult->text().left(ui->labelResult->text().indexOf(' ')).size());

    ui->labelResult->setText("Result:");
    ui->lineEditNum->setText(temp);
}

void WindowNumParse::switchValidators() {
    switch (ui->comboBoxFrom->currentIndex()) {
        case 0: // Default choice
            ui->lineEditNum->setValidator(nullptr);

            break;
        case 1: // BIN
            ui->lineEditNum->setValidator(binValidator);

            break;
        case 2: // DEC
            ui->lineEditNum->setValidator(decValidator);

            break;
        case 3: // OCT
            ui->lineEditNum->setValidator(octValidator);

            break;
        case 4: // HEX
            ui->lineEditNum->setValidator(hexValidator);

            break;
        default:
            qDebug() << "Invalid choice" << Qt::endl;

            return;
    }
}