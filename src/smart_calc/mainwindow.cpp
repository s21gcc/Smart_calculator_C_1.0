#include "mainwindow.h"

#include "graph.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  math_graph = new graph();

  connect(this, &MainWindow::signalBase, math_graph, &graph::slot);
  connect(math_graph, &graph::signal, this, &MainWindow::show);
  connect(math_graph, &graph::open_main_signal, this, &MainWindow::open_window);

  connect(ui->number_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->number_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->number_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->number_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->number_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->number_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->number_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->number_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->number_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->number_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->x, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->sin, SIGNAL(clicked()), this, SLOT(trigonom_operations()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(trigonom_operations()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(trigonom_operations()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(trigonom_operations()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(trigonom_operations()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(trigonom_operations()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(trigonom_operations()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(trigonom_operations()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(trigonom_operations()));

  connect(ui->button_plus, SIGNAL(clicked()), this, SLOT(simple_operations()));
  connect(ui->button_minus, SIGNAL(clicked()), this, SLOT(simple_operations()));
  connect(ui->button_div, SIGNAL(clicked()), this, SLOT(simple_operations()));
  connect(ui->button_mult, SIGNAL(clicked()), this, SLOT(simple_operations()));
  connect(ui->button_open, SIGNAL(clicked()), this, SLOT(simple_operations()));
  connect(ui->button_close, SIGNAL(clicked()), this, SLOT(simple_operations()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(simple_operations()));
  connect(ui->button_pow, SIGNAL(clicked()), this, SLOT(simple_operations()));
  connect(ui->button_dot, SIGNAL(clicked()), this, SLOT(simple_operations()));

  connect(ui->clear_str, SIGNAL(clicked()), this, SLOT(clear_str()));
  connect(ui->show_result, SIGNAL(clicked()), this, SLOT(show_result()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::keyPressEvent(QKeyEvent *e) {
  // QString new_label;

  if (e->key() == Qt::Key_0) {
    if (ui->x_window->text().isEmpty()) {
      ui->x_window->setText(ui->x_window->text() + "0.");
    } else {
      ui->x_window->setText(ui->x_window->text() + "0");
    }
  }
  if (e->key() == Qt::Key_1) {
    ui->x_window->setText(ui->x_window->text() + "1");
  }
  if (e->key() == Qt::Key_2) {
    ui->x_window->setText(ui->x_window->text() + "2");
  }
  if (e->key() == Qt::Key_3) {
    ui->x_window->setText(ui->x_window->text() + "3");
  }
  if (e->key() == Qt::Key_4) {
    ui->x_window->setText(ui->x_window->text() + "4");
  }
  if (e->key() == Qt::Key_5) {
    ui->x_window->setText(ui->x_window->text() + "5");
  }
  if (e->key() == Qt::Key_6) {
    ui->x_window->setText(ui->x_window->text() + "6");
  }
  if (e->key() == Qt::Key_7) {
    ui->x_window->setText(ui->x_window->text() + "7");
  }
  if (e->key() == Qt::Key_8) {
    ui->x_window->setText(ui->x_window->text() + "8");
  }
  if (e->key() == Qt::Key_9) {
    ui->x_window->setText(ui->x_window->text() + "9");
  }
  if (e->key() == Qt::Key_Comma && !ui->x_window->text().isEmpty() &&
      !ui->x_window->text().contains('.')) {
    ui->x_window->setText(ui->x_window->text() + ".");
  }
}

void MainWindow::open_window() { this->show(); }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->result_window->text() + button->text();
  ui->result_window->setText(new_label);
}

void MainWindow::trigonom_operations() {
  QPushButton *button = (QPushButton *)sender();
  ui->result_window->setText(ui->result_window->text() + button->text() + "(");
}

void MainWindow::simple_operations() {
  QPushButton *button = (QPushButton *)sender();
  ui->result_window->setText(ui->result_window->text() + button->text());
}

void MainWindow::clear_str() {
  ui->result_window->setText("");
  ui->x_window->setText("");
}

void MainWindow::show_result() {
  std::string str = ui->result_window->text().toStdString();
  std::string x_str = ui->x_window->text().toStdString();
  char *expression = &str[0];
  char *x_value = &x_str[0];
  double res = 0.0;
  double x = atof(x_value);
  int check = OK;
  check = start(expression, &res, x);
  QString num1 = QString::number(res, 'g', 9);
  ui->result_window->setText(num1);
  if (check == OK) {
    ui->check_valid->setText("OK");
  } else if (check == ERROR) {
    ui->check_valid->setText("ERROR");
  } else if (check == NaN) {
    ui->check_valid->setText("NaN");
  } else if (check == InF) {
    ui->check_valid->setText("InF");
  }
}

void MainWindow::on_build_graph_clicked() {
  emit signalBase(ui->result_window->text(), ui->x_min->text(),
                  ui->x_max->text(), ui->y_min->text(), ui->y_max->text());
  math_graph->show();
  this->close();
}
