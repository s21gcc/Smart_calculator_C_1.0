#include "graph.h"

#include "ui_graph.h"

graph::graph(QWidget *parent) : QWidget(parent), ui(new Ui::graph) {
  ui->setupUi(this);
}

void graph::slot(QString qstr, QString Xmin, QString Xmax, QString Ymin,
                 QString Ymax) {
  std::string str0 = qstr.toStdString();
  char *strRes = &str0[0];
  std::string str = Xmin.toStdString();
  char *startX = &str[0];
  std::string str1 = Xmax.toStdString();
  char *finishX = &str1[0];
  std::string str2 = Ymin.toStdString();
  char *startY = &str2[0];
  std::string str3 = Ymax.toStdString();
  char *finishY = &str3[0];

  double MinX = atof(startX);
  double MaxX = atof(finishX);
  double MinY = atof(startY);
  double MaxY = atof(finishY);
  double h = (MaxX - MinX) / 10000;

  if (MinX < MaxX && MinY < MaxY) {
    QVector<double> x, y;
    x.clear();
    y.clear();

    ui->graf->clearGraphs();

    for (double X = MinX; X <= MaxX; X += h) {
      double Y = 0;
      start(strRes, &Y, X);
      if (Y < MinY) Y = qQNaN();
      if (Y > MaxY) Y = qQNaN();
      x.push_back(X);
      y.push_back(Y);
    }

    ui->graf->xAxis->setRange(MinX, MaxX);
    ui->graf->yAxis->setRange(MinY, MaxY);
    ui->graf->addGraph();
    ui->graf->graph(0)->addData(x, y);
    ui->graf->replot();
    x.clear();
    y.clear();
  }
}

void graph::on_pushButton_clicked() {
  emit open_main_signal();
  this->close();
}

graph::~graph() { delete ui; }
