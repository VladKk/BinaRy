#ifndef WINDOW_NUM_PARSE_H
#define WINDOW_NUM_PARSE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WindowNumParse; }
QT_END_NAMESPACE

class WindowNumParse : public QMainWindow {
Q_OBJECT

public:
    explicit WindowNumParse(QWidget *parent = nullptr);

    ~WindowNumParse() final;

private slots:

    void actions();

    void back();

private:
    Ui::WindowNumParse *ui;
};

#endif //WINDOW_NUM_PARSE_H
