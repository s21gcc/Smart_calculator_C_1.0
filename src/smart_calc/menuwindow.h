#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>

#include "credit.h"
#include "mainwindow.h"

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QWidget {
  Q_OBJECT

 public:
  explicit MenuWindow(QWidget *parent = nullptr);
  ~MenuWindow();

 private slots:
  void on_simple_calc_clicked();

  void on_credit_calc_clicked();

 private:
  Ui::MenuWindow *ui;
  MainWindow main_window;
  Credit credit_window;
};

#endif  // MENUWINDOW_H
