#include <QMessageBox>
#include <QDebug>

#include "window_char_parse.h"
#include "./ui_window_char_parse.h"

// Create WindowCharParse object with validator
WindowCharParse::WindowCharParse(QWidget *parent) :
        QMainWindow(parent),
        binRegExpVal(new QRegExpValidator(QRegExp("[01]{0,}"), this)),
        ui(new Ui::WindowCharParse) {
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
    connect(ui->actionShow_ASCII_table, SIGNAL(triggered()), this, SLOT(actions()));

    connect(ui->buttonBack, SIGNAL(pressed()), this, SLOT(back()));

    connect(ui->buttonSwap, SIGNAL(pressed()), this, SLOT(swap()));

    connect(ui->buttonTranslate, SIGNAL(pressed()), this, SLOT(parse()));
}

WindowCharParse::~WindowCharParse() {
    delete ui;
    delete binRegExpVal;
}

void WindowCharParse::actions() {
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
    } else if (action == ui->actionShow_ASCII_table) {
        // Create and show custom message box to show ASCII table
        QMessageBox msgBox;

        msgBox.setWindowTitle("BinaRy");
        msgBox.setIconPixmap(QPixmap(":images/asciiTable.jpg"));
        msgBox.show();
        msgBox.exec();
    } else if (action == ui->actionRefresh) {
        // Clear everything
        ui->lineEdit->clear();
        ui->labelResult->setText("Result: ");
    } else if (action == ui->actionExit)
        QApplication::quit();
    else {
        qDebug() << "Invalid action!" << Qt::endl;

        QApplication::exit(EXIT_FAILURE);
    }
}

void WindowCharParse::back() {
    // Return to main window and keep this window hidden
    QMainWindow::parentWidget()->show();

    this->hide();
}

void WindowCharParse::swap() {
    // Swap text from line edit and result label
    QString temp = ui->labelResult->text().mid(
            ui->labelResult->text().indexOf(' ') + 1,
            ui->labelResult->text().size() -
            ui->labelResult->text().left(ui->labelResult->text().indexOf(' ')).size());

    temp.remove('\n');
    ui->labelResult->setText("Result:");
    ui->lineEdit->setText(temp);

    // Set validator depending on text/code to be parsed
    if (ui->lineEdit->placeholderText() == "Enter text here") {
        ui->lineEdit->setPlaceholderText("Enter binary code here");
        ui->lineEdit->setValidator(binRegExpVal);
    } else {
        ui->lineEdit->setPlaceholderText("Enter text here");
        ui->lineEdit->setValidator(nullptr);
    }
}

void WindowCharParse::parse() {
    // Check user to enter text in line edit
    if (ui->lineEdit->text().isEmpty())
        ui->statusBar->showMessage("Line edit shouldn`t be empty", 5000);

    // If text is need to be parsed
    if (ui->lineEdit->placeholderText() == "Enter text here") {
        // Get every character from line edit
                foreach(const auto &ch, ui->lineEdit->text()) {
                // Show result in binary code
                ui->labelResult->setText("Result: " + checkBinNum(ch));

                // If character is space, make gap to place code more compactly
                if (ch == ' ')
                    ui->labelResult->setText("Result: " + checkBinNum(ch) + '\n');
            }
        // If binary code is need to be parsed
    } else {
        // Check code format
        if ((ui->lineEdit->text().size() % 8) != 0) {
            qDebug() << "Invalid binary code!" << Qt::endl;

            ui->statusBar->showMessage("Invalid binary code", 5000);

            return;
        }

        // Temporary vectors to keep words and characters
        QVector<QString> tempStrVec;
        QVector<unsigned> tempNumVec;

        // Get every 8 numbers from code ann push them into tempStrVec
        for (int i = 0; i < ui->lineEdit->text().size(); i += 8)
            tempStrVec.push_back(ui->lineEdit->text().mid(i, 8));

        // Get every number from tempStrVec, parse it to unsigned int and push it into tempNumVec
                foreach(auto str, tempStrVec) tempNumVec.push_back(str.toUInt(nullptr, 2));

        // Clear all unnecessary spaces
        for (int i = 0; i < tempNumVec.size(); ++i) {
            if (tempNumVec.at(i) == (unsigned) ' ' && tempNumVec.at(i) == tempNumVec.at(i + 1))
                tempNumVec.erase(tempNumVec.begin() + i);
        }

        // Show result in chars
                foreach(auto val, tempNumVec) ui->labelResult->setText((QString) "Result: " + (QChar) val);
    }
}

QString WindowCharParse::checkBinNum(const QChar &ch) {
    // Parse character into binary code
    QString temp = QString::number(ch.unicode(), 2);

    // Check if binary code has 8 characters
    if ((temp.size() % 8) != 0) {
        do
            temp.push_front('0');
        while (temp.size() != 8);
    }

    return temp;
}

