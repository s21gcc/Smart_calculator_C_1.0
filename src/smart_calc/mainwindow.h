#ifndef MAINWINDOW_H
#define MAINWINDOW_H

extern "C" {
#include "calc.h"
}

#include <graph.h>

#include <QKeyEvent>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 signals:
  void signalBase(QString, QString, QString, QString, QString);

 private:
  Ui::MainWindow *ui;
  graph *math_graph;

 protected:
  void keyPressEvent(QKeyEvent *e) override;

 public slots:
  void open_window();

 private slots:
  void digits_numbers();
  void trigonom_operations();
  void simple_operations();
  void clear_str();
  void show_result();
  void on_build_graph_clicked();
};

#endif  // MAINWINDOW_H
