#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include <QWidget>
#include <QtMath>

extern "C" {
#include "calc.h"
}

namespace Ui {
class graph;
}

class graph : public QWidget {
  Q_OBJECT

 public:
  explicit graph(QWidget *parent = nullptr);
  ~graph();

 signals:
  void signal();
  void open_main_signal();

 private:
  Ui::graph *ui;

 public slots:
  void slot(QString qstr, QString Xmin, QString Xmax, QString Ymin,
            QString Ymax);

 private slots:
  void on_pushButton_clicked();
};

#endif  // GRAPH_H
