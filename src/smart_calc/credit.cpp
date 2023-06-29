#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QWidget(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  ui->spinBox_period->setSuffix(" m");
  ui->SpinBox_credit_sum->setSuffix(" $");
  ui->SpinBox_percents->setSuffix(" %");
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_clicked() {
  double total_amount = ui->SpinBox_credit_sum->value();
  double percents = ui->SpinBox_percents->value();
  int term = ui->spinBox_period->value();
  double monthly_pay = 0;
  double first_pay = 0;
  double overpay = 0;
  double total_pay = 0;
  if (ui->radioButton_Dif->isChecked()) {
    credit(&total_amount, term, percents, &monthly_pay, &first_pay, &overpay,
           &total_pay, 0);
    printf("%lf", monthly_pay);
    ui->last_pay->setText(QString::number(monthly_pay, 'f', 2));
    ui->first_pay->setText(QString::number(first_pay, 'f', 2));
  } else {
    credit(&total_amount, term, percents, &monthly_pay, &first_pay, &overpay,
           &total_pay, 1);
    if (isnan(monthly_pay) || isinf(monthly_pay)) {
      monthly_pay = 0;
      overpay = 0;
      total_pay = 0;
    }
    ui->first_pay->setText(QString::number(monthly_pay, 'f', 2));
    ui->last_pay->setText("");
  }
  ui->overpay->setText(QString::number(overpay, 'f', 2));
  ui->total_pay->setText(QString::number(total_pay, 'f', 2));
}
