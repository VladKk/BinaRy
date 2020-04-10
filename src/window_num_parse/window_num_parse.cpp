#include <QMessageBox>
#include <QDebug>

#include "window_num_parse.h"
#include "./ui_window_num_parse.h"

// Create WindowNumParse object with validators
WindowNumParse::WindowNumParse(QWidget *parent) :
        QMainWindow(parent),
        binValidator(new QRegExpValidator(QRegExp("[01]{0,}"), this)),
        decValidator(new QRegExpValidator(QRegExp("[0-9]{0,}"), this)),
        octValidator(new QRegExpValidator(QRegExp("[0-8]{0,}"), this)),
        hexValidator(new QRegExpValidator(QRegExp("[0-9A-F]{0,}"), this)),
        ui(new Ui::WindowNumParse) {
    // Set window icon and setup ui
    setWindowIcon(QIcon(":/icons/windowIcon.ico"));

    ui->setupUi(this);

    // Set icon on swap button
    ui->buttonSwap->setIcon(QIcon(":/icons/swapIcon.ico"));

    // Connect needed ui elements to actions
    connect(ui->actionAbout_developer, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionAbout_program, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionRefresh, SIGNAL(triggered()), this, SLOT(actions()));

    connect(ui->comboBoxFrom, SIGNAL(currentIndexChanged(int)), this, SLOT(switchValidators()));

    connect(ui->lineEditNum, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdit()));

    connect(ui->buttonBack, SIGNAL(pressed()), this, SLOT(back()));

    connect(ui->buttonSwap, SIGNAL(pressed()), this, SLOT(swap()));

    connect(ui->buttonTranslate, SIGNAL(pressed()), this, SLOT(translate()));
}

WindowNumParse::~WindowNumParse() {
    delete ui;
    delete binValidator;
    delete decValidator;
    delete octValidator;
    delete hexValidator;
}

void WindowNumParse::actions() {
    // Receive signal from action
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
        // Clear everything
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
    // Return to main window and keep this window hidden
    QMainWindow::parentWidget()->show();

    this->hide();
}

void WindowNumParse::swap() {
    // Swap texts in line edit and result label
    QString temp = ui->labelResult->text().mid(
            ui->labelResult->text().indexOf(' ') + 1,
            ui->labelResult->text().size() -
            ui->labelResult->text().left(ui->labelResult->text().indexOf(' ')).size());

    ui->labelResult->setText("Result:");
    ui->lineEditNum->setText(temp);

    // Swap options
    int tmpIndex = ui->comboBoxFrom->currentIndex();
    ui->comboBoxFrom->setCurrentIndex(ui->comboBoxTo->currentIndex());
    ui->comboBoxTo->setCurrentIndex(tmpIndex);
}

void WindowNumParse::translate() {
    // Check user to choose not the same operations and enter text
    if (ui->comboBoxFrom->currentIndex() == 0 || ui->comboBoxTo->currentIndex() == 0) {
        ui->statusBar->showMessage("Choose one of the options to translate", 5000);

        return;
    }

    if (ui->lineEditNum->text().isEmpty()) {
        ui->statusBar->showMessage("Enter number to translate", 5000);

        return;
    }

    if (ui->comboBoxFrom->currentIndex() == ui->comboBoxTo->currentIndex()) {
        ui->statusBar->showMessage("It is pointless to translate the same numeric system", 5000);

        return;
    }

    // Store entered code as decimal number
    qint64 num;

    switch (ui->comboBoxFrom->currentIndex()) {
        case 1: // BIN
            num = ui->lineEditNum->text().toLongLong(nullptr, 2);

            break;
        case 2: // DEC
            num = ui->lineEditNum->text().toLongLong(nullptr, 10);

            break;
        case 3: // OCT
            num = ui->lineEditNum->text().toLongLong(nullptr, 8);

            break;
        case 4: // HEX
            num = ui->lineEditNum->text().toLongLong(nullptr, 16);

            break;
        default:
            qDebug() << "Invalid choice" << Qt::endl;

            return;
    }

    // Show result depending on chosen option
    switch (ui->comboBoxTo->currentIndex()) {
        case 1: // BIN
            ui->labelResult->setText("Result: " + QString::number(num, 2));

            break;
        case 2: // DEC
            ui->labelResult->setText("Result: " + QString::number(num, 10));

            break;
        case 3: // OCT
            ui->labelResult->setText("Result: " + QString::number(num, 8));

            break;
        case 4: // HEX
            ui->labelResult->setText("Result: " + QString::number(num, 16).toUpper());

            break;
        default:
            qDebug() << "Invalid choice" << Qt::endl;

            return;
    }
}

void WindowNumParse::switchValidators() {
    // Set validator depending on chosen option
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

void WindowNumParse::checkLineEdit() {
    // Check the user to choose the option before enter the text
    if (!ui->lineEditNum->text().isEmpty() && ui->comboBoxFrom->currentIndex() == 0) {
        ui->statusBar->showMessage("Choose the option first", 5000);

        ui->lineEditNum->clear();

        return;
    }
}