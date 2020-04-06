#ifndef WINDOW_CHAR_PARSE_H
#define WINDOW_CHAR_PARSE_H

#include <QMainWindow>
#include <QRegExpValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class WindowCharParse; }
QT_END_NAMESPACE

class WindowCharParse : public QMainWindow {
Q_OBJECT

public:
    explicit WindowCharParse(QWidget *parent = nullptr);

    ~WindowCharParse() final;

private slots:

    void actions();

    void back();

    void swap();

    void parse();

private:
    Ui::WindowCharParse *ui;

    QRegExpValidator *binRegExpVal;

    static QString checkBinNum(const QChar &ch);
};

#endif //WINDOW_CHAR_PARSE_H
