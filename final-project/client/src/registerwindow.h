#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class RegisterWindow;
}
QT_END_NAMESPACE

class RegisterWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::RegisterWindow *ui;
};

#endif// REGISTERWINDOW_H
