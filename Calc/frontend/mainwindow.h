#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleValidator>
#include <QIntValidator>
#include <QMainWindow>
#include <QVector>

#include "qcustomplot.h"
extern "C" {
#include "../s21_calc.h"
#include "../s21_credit.h"
}
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

 private slots:

  void on_button_1_clicked();

  void on_button_2_clicked();

  void on_button_3_clicked();

  void on_button_4_clicked();

  void on_button_5_clicked();

  void on_button_6_clicked();

  void on_button_plus_clicked();

  void on_button_AC_clicked();

  void on_button_rez_clicked();

  void on_button_minus_clicked();

  void on_button_mul_clicked();

  void on_button_div_clicked();

  void on_button_ln_clicked();

  void on_button_log_clicked();

  void on_button_sqrt_clicked();

  void on_button_pow_clicked();

  void on_button_sin_clicked();

  void on_button_cos_clicked();

  void on_button_tan_clicked();

  void on_button_asin_clicked();

  void on_button_acos_clicked();

  void on_button_atan_clicked();

  void on_button_mod_clicked();

  void on_button_bo_clicked();

  void on_button_bc_clicked();

  int simple_operator_input_check(QString *user, QString *back);

  int for_unar_check(QString backendstring);

  int for_digits(QString backendstring);

  void on_button_X_clicked();

  void on_button_7_clicked();

  void on_button_8_clicked();

  void on_button_9_clicked();

  void on_button_0_clicked();

  void on_button_dot_clicked();

  void validators();

  void on_button_graph_clicked();

  void wheelEvent(QWheelEvent *event);

  void updateGraph(double xmin, double xmax, double ymin, double ymax,
                   double h);

  void onAxisRangeChanged(const QCPRange &newRange);

  void credit();

  void on_rez_button_clicked();

  int year_to_month_convert(QString string);

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
