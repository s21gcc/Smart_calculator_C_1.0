#include <QApplication>

#include "mainwindow.h"
#include "menuwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MenuWindow w;
  w.show();
  return a.exec();
}
