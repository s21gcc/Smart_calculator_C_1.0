#include "menuwindow.h"

#include "ui_credit.h"
#include "ui_menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MenuWindow) {
  ui->setupUi(this);
}

MenuWindow::~MenuWindow() { delete ui; }

void MenuWindow::on_simple_calc_clicked() {
  main_window.show();
  this->close();
}

void MenuWindow::on_credit_calc_clicked() {
  credit_window.show();
  this->close();
}
