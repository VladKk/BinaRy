#ifndef WINDOW_LOGIC_H
#define WINDOW_LOGIC_H

#include <QMainWindow>

// Place WindowLogic class into Ui namespace to create ui
QT_BEGIN_NAMESPACE
namespace Ui { class WindowLogic; }
QT_END_NAMESPACE

class WindowLogic : public QMainWindow {
Q_OBJECT

public:
    explicit WindowLogic(QWidget *parent = nullptr);

    ~WindowLogic() final;

private slots:

    void actions();

    void back();

    void swap();

    void calculate();

    void changeUi();

private:
    Ui::WindowLogic *ui;
};

#endif //WINDOW_LOGIC_H
