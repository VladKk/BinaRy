#ifndef WINDOW_NUM_PARSE_H
#define WINDOW_NUM_PARSE_H

#include <QMainWindow>
#include <QRegExpValidator>

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

    void switchValidators();

    void swap();

    void translate();

private:
    Ui::WindowNumParse *ui;

    QRegExpValidator *binValidator;
    QRegExpValidator *decValidator;
    QRegExpValidator *octValidator;
    QRegExpValidator *hexValidator;
};

#endif //WINDOW_NUM_PARSE_H
