#ifndef WINDOW_ARITHMETIC_H
#define WINDOW_ARITHMETIC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WindowArithmetic; }
QT_END_NAMESPACE

class WindowArithmetic : public QMainWindow {
Q_OBJECT

public:
    explicit WindowArithmetic(QWidget *parent = nullptr);

    ~WindowArithmetic() final;

private slots:

    void actions();

    void back();

    void calculate();

    void swap();

private:
    Ui::WindowArithmetic *ui;
};

#endif //WINDOW_ARITHMETIC_H
