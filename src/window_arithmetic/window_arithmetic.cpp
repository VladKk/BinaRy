#include <QMessageBox>
#include <QDebug>

#include "window_arithmetic.h"
#include "./ui_window_arithmetic.h"

WindowArithmetic::WindowArithmetic(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::WindowArithmetic) {
    // Set window icon and setup ui
    setWindowIcon(QIcon(":/icons/windowIcon.ico"));

    ui->setupUi(this);

    // Set icon on swap button
    ui->buttonSwap->setIcon(QIcon(":/icons/swapIcon.ico"));

    // Set validators for binary code
    ui->lineEditLower->setValidator(new QRegExpValidator(QRegExp("[01]{0,}"), this));
    ui->lineEditUpper->setValidator(new QRegExpValidator(QRegExp("[01]{0,}"), this));

    // Connect needed ui elements to actions
    connect(ui->actionAbout_developer, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionAbout_program, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionRefresh, SIGNAL(triggered()), this, SLOT(actions()));

    connect(ui->buttonBack, SIGNAL(pressed()), this, SLOT(back()));

    connect(ui->buttonSwap, SIGNAL(pressed()), this, SLOT(swap()));

    connect(ui->buttonCalculate, SIGNAL(pressed()), this, SLOT(calculate()));
}

WindowArithmetic::~WindowArithmetic() { delete ui; }

void WindowArithmetic::actions() {
    // Receive signal from action
    auto *action = (QAction *) sender();

    // Trigger action
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
        // Clear everything
        ui->lineEditUpper->clear();
        ui->lineEditLower->clear();
        ui->labelResult->setText("Result:");
        ui->comboBoxOps->setCurrentIndex(0);
    } else if (action == ui->actionExit)
        QApplication::quit();
    else {
        qDebug() << "Invalid action!" << Qt::endl;

        QApplication::exit(EXIT_FAILURE);
    }
}

void WindowArithmetic::back() {
    // Return to main window and keep this window hidden
    QMainWindow::parentWidget()->show();

    this->hide();
}

void WindowArithmetic::swap() {
    // Swap text in upper and lower line edits
    QString temp = ui->lineEditUpper->text();
    ui->lineEditUpper->setText(ui->lineEditLower->text());
    ui->lineEditLower->setText(temp);
}

void WindowArithmetic::calculate() {
    // Check the user to choose option and enter text in line edits
    if (ui->comboBoxOps->currentIndex() == 0) {
        ui->statusBar->showMessage("Choose the operation", 5000);

        return;
    }

    if (ui->lineEditLower->text().isEmpty() || ui->lineEditUpper->text().isEmpty()) {
        ui->statusBar->showMessage("Line edits shouldn`t be empty", 5000);

        return;
    }

    // Temporary parse binary code to decimal numbers
    qint64 num1 = ui->lineEditUpper->text().toLongLong(nullptr, 2);
    qint64 num2 = ui->lineEditLower->text().toLongLong(nullptr, 2);

    // Show result depending on chosen operation
    switch (ui->comboBoxOps->currentIndex()) {
        case 1: // +
            ui->labelResult->setText("Result: " + QString::number(num1 + num2, 2));

            break;
        case 2: // -
            ui->labelResult->setText("Result: " + QString::number(num1 - num2, 2));

            break;
        case 3: // *
            ui->labelResult->setText("Result: " + QString::number(num1 * num2, 2));

            break;
        case 4: // /
            ui->labelResult->setText("Result: " + QString::number(num1 / num2, 2));

            break;
        default:
            qDebug() << "Invalid operation" << Qt::endl;

            QApplication::exit(EXIT_FAILURE);
    }
}