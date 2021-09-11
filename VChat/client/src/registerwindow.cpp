#include "registerwindow.h"
#include "./ui_registerwindow.h"

RegisterWindow::RegisterWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::RegisterWindow) {
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow() { delete ui; }

void RegisterWindow::on_pushButton_2_clicked() {}


void RegisterWindow::on_pushButton_clicked() {}
