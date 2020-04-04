#ifndef WINDOW_LOGIC_H
#define WINDOW_LOGIC_H

#include <QMainWindow>

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

private:
    Ui::WindowLogic *ui;
};

#endif //WINDOW_LOGIC_H
