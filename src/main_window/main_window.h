#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "../window_arithmetic/window_arithmetic.h"
#include "../window_logic/window_logic.h"
#include "../window_char_parse/window_char_parse.h"
#include "../window_num_parse/window_num_parse.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() final;

private slots:

    void actions();

    void opsRedirect();

private:
    Ui::MainWindow *ui;

    WindowLogic *winLogic;
    WindowArithmetic *winArithmetic;
    WindowCharParse *winCharParse;
    WindowNumParse *winNumParse;

    template<typename T>
    T *getInstance(T *instance);
};

#endif //MAIN_WINDOW_H
