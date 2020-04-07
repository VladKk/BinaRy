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
    } else if (action == ui->actionShow_ASCII_table) {
        QMessageBox msgBox;

        msgBox.setWindowTitle("BinaRy");
        msgBox.setIconPixmap(QPixmap(":images/asciiTable.jpg"));
        msgBox.show();
        msgBox.exec();
    } else if (action == ui->actionRefresh) {
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
    QMainWindow::parentWidget()->show();

    this->hide();
}

void WindowCharParse::swap() {
    QString temp = ui->labelResult->text().mid(
            ui->labelResult->text().indexOf(' ') + 1,
            ui->labelResult->text().size() -
            ui->labelResult->text().left(ui->labelResult->text().indexOf(' ')).size());

    temp.remove('\n');
    ui->labelResult->setText("Result:");
    ui->lineEdit->setText(temp);

    if (ui->lineEdit->placeholderText() == "Enter text here") {
        ui->lineEdit->setPlaceholderText("Enter binary code here");
        ui->lineEdit->setValidator(binRegExpVal);
    } else {
        ui->lineEdit->setPlaceholderText("Enter text here");
        ui->lineEdit->setValidator(nullptr);
    }
}

void WindowCharParse::parse() {
    if (ui->lineEdit->text().isEmpty())
        ui->statusBar->showMessage("Line edit shouldn`t be empty", 5000);

    ui->labelResult->setText("Result: ");

    if (ui->lineEdit->placeholderText() == "Enter text here") {
                foreach(const auto &ch, ui->lineEdit->text()) {
                ui->labelResult->setText(ui->labelResult->text() + checkBinNum(ch));

                if (ch == ' ')
                    ui->labelResult->setText(ui->labelResult->text() + checkBinNum(ch) + '\n');
            }
    } else {
        if ((ui->lineEdit->text().size() % 8) != 0) {
            qDebug() << "Invalid binary code!" << Qt::endl;

            ui->statusBar->showMessage("Invalid binary code", 5000);

            return;
        }

        QVector<QString> tempStrVec;
        QVector<unsigned> tempNumVec;

        for (int i = 0; i < ui->lineEdit->text().size(); i += 8)
            tempStrVec.push_back(ui->lineEdit->text().mid(i, 8));

                foreach(auto str, tempStrVec) tempNumVec.push_back(str.toUInt(nullptr, 2));

        for (int i = 0; i < tempNumVec.size(); ++i) {
            if (tempNumVec.at(i) == (unsigned) ' ' && tempNumVec.at(i) == tempNumVec.at(i + 1))
                tempNumVec.erase(tempNumVec.begin() + i);
        }

                foreach(auto val, tempNumVec) ui->labelResult->setText(ui->labelResult->text() + (QChar) val);
    }
}

QString WindowCharParse::checkBinNum(const QChar &ch) {
    QString temp = QString::number(ch.unicode(), 2);

    if ((temp.size() % 8) != 0) {
        do
            temp.push_front('0');
        while (temp.size() != 8);
    }

    return temp;
}

