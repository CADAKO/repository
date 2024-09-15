#include "mainwindow.h"

#include <QWheelEvent>

#include "ui_mainwindow.h"

QString userstring = "";
QString backendstring = "";
double lastXMax = 1, lastYMax = 1, lastXMin = -1, lastYMin = -1, lastH = 0.02;
int bracketscount = 0;
int dotcount = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->widget->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);
  validators();
  connect(ui->widget->xAxis, SIGNAL(rangeChanged(const QCPRange &)), this,
          SLOT(onAxisRangeChanged(const QCPRange &)));
  connect(ui->widget->yAxis, SIGNAL(rangeChanged(const QCPRange &)), this,
          SLOT(onAxisRangeChanged(const QCPRange &)));
}

void MainWindow::validators() {
  QDoubleValidator *vfx =
      new QDoubleValidator(-(__DBL_MAX__), __DBL_MAX__, 7, this);
  vfx->setNotation(QDoubleValidator::StandardNotation);
  ui->edit_x->setValidator(vfx);
  QDoubleValidator *for_bank = new QDoubleValidator(0, __DBL_MAX__, 2, this);
  for_bank->setNotation(QDoubleValidator::StandardNotation);
  QDoubleValidator *for_bank_p = new QDoubleValidator(0, __DBL_MAX__, 7, this);
  for_bank_p->setNotation(QDoubleValidator::StandardNotation);
  ui->edit_percent->setValidator(for_bank_p);
  ui->edit_sum->setValidator(for_bank);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_button_1_clicked() {
  if (!for_digits(backendstring)) {
    userstring.push_back('1');
    backendstring.push_back('1');
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_2_clicked() {
  if (!for_digits(backendstring)) {
    userstring.push_back('2');
    backendstring.push_back('2');
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_3_clicked() {
  if (!for_digits(backendstring)) {
    userstring.push_back('3');
    backendstring.push_back('3');
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_4_clicked() {
  if (!for_digits(backendstring)) {
    userstring.push_back('4');
    backendstring.push_back('4');
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_5_clicked() {
  if (!for_digits(backendstring)) {
    userstring.push_back('5');
    backendstring.push_back('5');
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_6_clicked() {
  if (!for_digits(backendstring)) {
    userstring.push_back('6');
    backendstring.push_back('6');
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_plus_clicked() {
  if (backendstring.isEmpty() || backendstring.right(1) == "(") {
    userstring.push_back('+');
    backendstring.push_back('#');
  } else {
    if (!simple_operator_input_check(&userstring, &backendstring)) {
      userstring.push_back('+');
      backendstring.push_back('+');
    }
  }
  dotcount = 0;
  ui->label_input->setText(userstring);
}

void MainWindow::on_button_AC_clicked() {
  userstring.clear();
  backendstring.clear();
  bracketscount = 0;
  dotcount = 0;
  ui->label_input->setText("0");
  ui->label_rez->clear();
  ui->widget->clearGraphs();
  ui->widget->replot();
}

void MainWindow::on_button_rez_clicked() {
  ui->label_rez->clear();
  QString backendstringtemp = backendstring;
  if (backendstringtemp.contains('X')) {
    double term = 0;
    if (ui->edit_x->text().length() > 0) {
      term = ui->edit_x->text().toDouble();
    }
    backendstringtemp.replace('X', QString::number(term));
    //        userstring.replace('X', QString::number(term));

    ui->label_input->setText(userstring);
  }
  //    if (backendstring.length() == 1 && (backendstring.contains("~") ||
  //    backendstring.contains("#")))
  if (!for_unar_check(backendstringtemp)) {
    ui->label_rez->setText(userstring);
  } else {
    QByteArray array = backendstringtemp.toLatin1();
    char *stringtocalc = array.data();
    if (calcbracketinfix(stringtocalc) == 0) {
      double res = calc(stringtocalc);
      ui->label_rez->setText(QString::number(res));
    } else {
      ui->label_rez->setText("Error");
    }
  }
  backendstringtemp.clear();
}

void MainWindow::on_button_minus_clicked() {
  if (backendstring.isEmpty() || backendstring.right(1) == "(") {
    userstring.push_back('-');
    backendstring.push_back('~');
  } else {
    if (!simple_operator_input_check(&userstring, &backendstring)) {
      userstring.push_back('-');
      backendstring.push_back('-');
    }
  }
  dotcount = 0;
  ui->label_input->setText(userstring);
}

void MainWindow::on_button_mul_clicked() {
  if (!simple_operator_input_check(&userstring, &backendstring))
    if (!backendstring.isEmpty() && backendstring.right(1) != "(") {
      userstring.push_back('*');
      backendstring.push_back('*');
      ui->label_input->setText(userstring);
      dotcount = 0;
    }
}

void MainWindow::on_button_div_clicked() {
  if (!simple_operator_input_check(&userstring, &backendstring))
    if (!backendstring.isEmpty() && backendstring.right(1) != "(") {
      userstring.push_back('/');
      backendstring.push_back('/');
      ui->label_input->setText(userstring);
      dotcount = 0;
    }
}

void MainWindow::on_button_ln_clicked() {
  if (!for_unar_check(backendstring)) {
    userstring.append("ln(");
    backendstring.append("L(");
    bracketscount++;
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_log_clicked() {
  if (!for_unar_check(backendstring)) {
    userstring.append("log(");
    backendstring.append("l(");
    bracketscount++;
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_sqrt_clicked() {
  if (!for_unar_check(backendstring)) {
    userstring.append("√(");
    backendstring.append("Q(");
    bracketscount++;
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_pow_clicked() {
  if (!simple_operator_input_check(&userstring, &backendstring))
    if (!backendstring.isEmpty() && backendstring.right(1) != "(") {
      userstring.push_back('^');
      backendstring.push_back('^');
      ui->label_input->setText(userstring);
      dotcount = 0;
    }
}

void MainWindow::on_button_sin_clicked() {
  if (!for_unar_check(backendstring)) {
    userstring.append("sin(");
    backendstring.append("s(");
    bracketscount++;
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_cos_clicked() {
  if (!for_unar_check(backendstring)) {
    userstring.append("cos(");
    backendstring.append("c(");
    bracketscount++;
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_tan_clicked() {
  if (!for_unar_check(backendstring)) {
    userstring.append("tan(");
    backendstring.append("t(");
    bracketscount++;
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_asin_clicked() {
  if (!for_unar_check(backendstring)) {
    userstring.append("asin(");
    backendstring.append("S(");
    bracketscount++;
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_acos_clicked() {
  if (!for_unar_check(backendstring)) {
    userstring.append("acos(");
    backendstring.append("C(");
    bracketscount++;
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_atan_clicked() {
  if (!for_unar_check(backendstring)) {
    userstring.append("atan(");
    backendstring.append("T(");
    bracketscount++;
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_mod_clicked() {
  if (!simple_operator_input_check(&userstring, &backendstring))
    if (!backendstring.isEmpty() && backendstring.right(1) != "(") {
      userstring.push_back('%');
      backendstring.push_back('%');
      ui->label_input->setText(userstring);
      dotcount = 0;
    }
}

void MainWindow::on_button_bo_clicked() {
  if (backendstring.right(1) != ")" && backendstring.right(1) != "X" &&
      backendstring.right(1) != ".") {
    if ((backendstring.isEmpty()) ||
        (!backendstring.isEmpty() && !userstring.right(1).at(0).isDigit())) {
      bracketscount++;
      userstring.push_back('(');
      backendstring.push_back('(');
      ui->label_input->setText(userstring);
    }
  }
}

void MainWindow::on_button_bc_clicked() {
  if (!simple_operator_input_check(&userstring, &backendstring))
    if (!backendstring.isEmpty() && backendstring.right(1) != "(" &&
        bracketscount != 0) {
      userstring.push_back(')');
      backendstring.push_back(')');
      bracketscount--;
      ui->label_input->setText(userstring);
      dotcount = 0;
    }
}

int MainWindow::simple_operator_input_check(QString *user, QString *back) {
  int err = 1;
  if (back->right(1) == "+" || back->right(1) == "-" || back->right(1) == "*" ||
      back->right(1) == "/" || back->right(1) == "%" || back->right(1) == "^" ||
      back->right(1) == "#" || back->right(1) == "~") {
    user->chop(1);
    back->chop(1);
    err = 0;
  }
  if (!back->isEmpty() && (user->right(1).at(0).isDigit() ||
                           back->right(1) == ")" || back->right(1) == "X"))
    err = 0;
  return err;
}

int MainWindow::for_unar_check(QString backendstring) {
  int err = 1;
  if (backendstring.right(1) == "+" || backendstring.right(1) == "^" ||
      backendstring.right(1) == "%" || backendstring.right(1) == "(" ||
      backendstring.right(1) == "#" || backendstring.right(1) == "~" ||
      backendstring.right(1) == "(" || backendstring.right(1) == "/" ||
      backendstring.right(1) == "*" || backendstring.right(1) == "-" ||
      backendstring.isEmpty())
    err = 0;
  return err;
}

int MainWindow::for_digits(QString backendstring) {
  int err = 0;
  if (backendstring.right(1) == "X" || backendstring.right(1) == ")") err = 1;
  return err;
}

void MainWindow::on_button_X_clicked() {
  if (!for_unar_check(backendstring)) {
    userstring.push_back('X');
    backendstring.push_back('X');
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_7_clicked() {
  if (!for_digits(backendstring)) {
    userstring.push_back('7');
    backendstring.push_back('7');
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_8_clicked() {
  if (!for_digits(backendstring)) {
    userstring.push_back('8');
    backendstring.push_back('8');
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_9_clicked() {
  userstring.push_back('9');
  backendstring.push_back('9');
  ui->label_input->setText(userstring);
}

void MainWindow::on_button_0_clicked() {
  if (!for_digits(backendstring)) {
    userstring.push_back('0');
    backendstring.push_back('0');
    ui->label_input->setText(userstring);
  }
}

void MainWindow::on_button_dot_clicked() {
  if (!backendstring.isEmpty() && userstring.right(1).at(0).isDigit() &&
      dotcount == 0) {
    userstring.push_back('.');
    backendstring.push_back('.');
    ui->label_input->setText(userstring);
    dotcount = 1;
  }
}

void MainWindow::updateGraph(double xmax, double ymax, double xmin, double ymin,
                             double h) {
  ui->widget->clearGraphs();
  ui->label_rez->clear();
  if (backendstring.contains('X')) {
    int N = (xmax - xmin) / h;
    QVector<double> x(N), y(N);
    QString temp = backendstring;
    QString replacement;
    for (int i = 0; i < N; ++i) {
      double X = xmin + i * h;
      x[i] = X;
      if (X < 0)
        replacement = "~" + QString::number(-X);
      else
        replacement = QString::number(X);
      temp.replace('X', replacement);
      QByteArray array = temp.toLatin1();
      if (calcbracketinfix(array.data()) == 0) {
        y[i] = calc(array.data());
      } else {
        ui->label_rez->setText("Error");
      }
      i++;

      temp = backendstring;
      replacement.clear();
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    ui->widget->xAxis->setLabel("X");
    ui->widget->yAxis->setLabel("-<");
    ui->widget->xAxis->setRange(xmin, xmax);
    ui->widget->yAxis->setRange(ymin, ymax);
    ui->widget->replot();
  }
}
void MainWindow::wheelEvent(QWheelEvent *event) {
  if (ui->widget->axisRect()->rect().contains(event->position().toPoint())) {
    double factor = 1.2;  // фактор масштабирования

    if (event->angleDelta().y() < 0) {
      // Приближение при прокрутке вперед
      ui->widget->xAxis->scaleRange(
          factor, ui->widget->xAxis->pixelToCoord(event->position().x()));
      ui->widget->yAxis->scaleRange(
          factor, ui->widget->yAxis->pixelToCoord(event->position().y()));
    } else {
      // Отдаление при прокрутке назад
      ui->widget->xAxis->scaleRange(
          1.0 / factor, ui->widget->xAxis->pixelToCoord(event->position().x()));
      ui->widget->yAxis->scaleRange(
          1.0 / factor, ui->widget->yAxis->pixelToCoord(event->position().y()));
    }
    event->accept();
  }
}

void MainWindow::onAxisRangeChanged(const QCPRange &newRange) {
  if (newRange.lower > -1000000) lastXMin = ui->widget->xAxis->range().lower;
  if (newRange.upper < 1000000) lastXMax = ui->widget->xAxis->range().upper;
  if (newRange.lower > -1000000) lastYMin = ui->widget->yAxis->range().lower;
  if (newRange.upper < 1000000) lastYMax = ui->widget->yAxis->range().upper;
  lastH = (lastXMax - lastXMin) / 100;
  updateGraph(lastXMax, lastYMax, lastXMin, lastYMin, lastH);
}

void MainWindow::on_button_graph_clicked() {
  updateGraph(lastXMax, lastYMax, lastXMin, lastYMin, lastH);
}

int MainWindow::year_to_month_convert(QString string) {
  int res = 0;
  if (string.contains("л") || string.contains("г")) {
    string = string.left(string.indexOf(" "));
    res = string.toInt() * 12;
  } else {
    string = string.left(string.indexOf(" "));
    res = string.toInt();
  }
  return res;
}

void MainWindow::credit() {
  double totalLoanAmount =
      ui->edit_sum->text().toDouble();  // Общая сумма кредита
  int termMonths = year_to_month_convert(
      ui->duration_box->currentText());  // Срок кредита в месяцах
  double interestRate =
      ui->edit_percent->text().toDouble();  // Процентная ставка
  int creditType =
      ui->credit_type_box
          ->currentIndex();  // Тип кредита (аннуитетный или дифференцированный)
  double monthlyPayments[termMonths] = {0};  // Создаем массив с нужным размером
  double overpayment = 0, totalPayment = 0;

  calculateCredit(totalLoanAmount, termMonths, interestRate, creditType,
                  monthlyPayments, &overpayment, &totalPayment);

  QString itemText = "";
  for (int i = 0; i < termMonths; ++i) {
    itemText = QString("%1 месяц: %2").arg(i + 1).arg(monthlyPayments[i]);
    ui->platezh_rez_box->addItem(itemText);
  }
  ui->pereplata_rez_label->setText(QString::number(overpayment, 'f', 2));
  ui->obsh_rez_label->setNum(totalPayment);
}

void MainWindow::on_rez_button_clicked() {
  ui->platezh_rez_box->clear();
  ui->pereplata_rez_label->clear();
  ui->obsh_rez_label->clear();
  if (ui->edit_sum->text().toDouble() > 0 &&
      ui->edit_percent->text().toDouble() >= 0) {
    credit();
  } else {
    ui->obsh_rez_label->setText("Введи корректные данные");
  }
}
