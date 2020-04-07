#include <QMessageBox>
#include <QDebug>
#include <QComboBox>

#include "window_logic.h"
#include "./ui_window_logic.h"

WindowLogic::WindowLogic(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::WindowLogic) {
    setWindowIcon(QIcon(":/icons/windowIcon.ico"));

    ui->setupUi(this);

    ui->buttonSwap->setIcon(QIcon(":/icons/swapIcon.ico"));

    ui->lineEditUpper->setValidator(new QRegExpValidator(QRegExp("[01]{0,64}"), this));
    ui->lineEdirLower->setValidator(new QRegExpValidator(QRegExp("[01]{0,64}"), this));
    ui->lineEditShift->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,2}"), this));

    ui->lineEditShift->hide();

    connect(ui->actionAbout_developer, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionAbout_program, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionRefresh, SIGNAL(triggered()), this, SLOT(actions()));

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeUi()));

    connect(ui->buttonBack, SIGNAL(pressed()), this, SLOT(back()));

    connect(ui->buttonSwap, SIGNAL(pressed()), this, SLOT(swap()));

    connect(ui->buttonCalculate, SIGNAL(pressed()), this, SLOT(calculate()));
}

WindowLogic::~WindowLogic() { delete ui; }

void WindowLogic::actions() {
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
        ui->lineEdirLower->clear();
        ui->lineEditShift->clear();
        ui->labelResult->setText("Result:");
        ui->comboBox->setCurrentIndex(0);
    } else if (action == ui->actionExit)
        QApplication::quit();
    else {
        qDebug() << "Invalid action!" << Qt::endl;

        QApplication::exit(EXIT_FAILURE);
    }
}

void WindowLogic::back() {
    QMainWindow::parentWidget()->show();

    this->hide();
}

void WindowLogic::swap() {
    QString temp = ui->lineEditUpper->text();
    ui->lineEditUpper->setText(ui->lineEdirLower->text());
    ui->lineEdirLower->setText(temp);
}

void WindowLogic::calculate() {
    if (ui->lineEdirLower->text().isEmpty() || ui->lineEditUpper->text().isEmpty()) {
        ui->statusBar->showMessage("Line edits shouldn't be empty", 5000);

        return;
    }

    if (ui->comboBox->currentIndex() == 0) {
        ui->statusBar->showMessage("Choose the operation", 5000);

        return;
    }

    quint64 num1 = ui->lineEditUpper->text().toULongLong(nullptr, 2);
    quint64 num2 = ui->lineEdirLower->text().toULongLong(nullptr, 2);

    switch (ui->comboBox->currentIndex()) {
        case 1: // AND
            ui->labelResult->setText("Result: " + QString::number(num1 & num2, 2));

            break;
        case 2: // OR
            ui->labelResult->setText("Result: " + QString::number(num1 | num2, 2));

            break;
        case 3: // XOR
            ui->labelResult->setText("Result: " + QString::number(num1 ^ num2, 2));

            break;
        case 4: // Left shift
            ui->labelResult->setText(
                    "Result: " + QString::number(num1 << ui->lineEditShift->text().toUShort(nullptr), 2));

            break;
        case 5: // Right shift
            ui->labelResult->setText(
                    "Result: " + QString::number(num1 >> ui->lineEditShift->text().toUShort(nullptr), 2));

            break;
        case 6: // NOT
            ui->labelResult->setText("Result: " + QString::number(~num1, 2));

            break;
        default:
            qDebug() << "Invalid operation" << Qt::endl;

            return;
    }
}

void WindowLogic::changeUi() {
    switch (ui->comboBox->currentIndex()) {
        case 0: // Default text
        case 1: // AND
        case 2: // OR
        case 3: // XOR
            ui->lineEdirLower->show();
            ui->lineEditShift->hide();

            break;
        case 4: // Left shift
        case 5: // Right shift
            ui->lineEdirLower->hide();
            ui->lineEditShift->show();

            break;
        case 6: // NOT
            ui->lineEdirLower->hide();
            ui->lineEditShift->hide();

            break;
        default:
            qDebug() << "Invalid operation" << Qt::endl;

            return;
    }
}