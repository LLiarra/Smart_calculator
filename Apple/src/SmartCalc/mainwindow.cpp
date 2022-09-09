#include "mainwindow.h"
#include "ui_mainwindow.h"

extern "C" {
  long double s21_smart_calc(char* work_str);
  int s21_is_not_valid(char* str);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_lbracket, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_rbracket, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::digits_numbers() {
    QPushButton *button = (QPushButton *)sender();
    check_func(button->text());
    ui->label_expression->setText(work_print_str);
    ui->label_expression->show();
}

void MainWindow::on_pushButton_del_symb_clicked() {
  int length = work_print_str.length();
  int length_back = work_back_str.length();
  if (!(work_print_str.isEmpty())) {
    if (work_print_str[length - 1] == 'X') {
      is_X = 0;
    }
    if (work_print_str[length - 1] == '.') {
        check_dot = 0;
    }
    work_print_str = work_print_str.remove(length - 1, 1);
    ui->label_expression->setText(work_print_str);
    if (work_back_str[length_back - 1] != ' ') {
      work_back_str = work_back_str.remove(length_back - 1, 1);
    } else {
      work_back_str = work_back_str.remove(length_back - 3, 3);
    }
  }
}

void MainWindow::on_pushButton_del_all_clicked() {
    work_back_str.clear();
    work_print_str.clear();
    ui->label_result->clear();
    ui->label_expression->clear();
    ui->widget->clearGraphs();
    ui->widget->replot();
    is_X = 0;
    check_dot = 0;
}

void MainWindow::check_unary() {
  if (work_print_str.isEmpty()) {
      work_back_str.push_back("0");
  } else {
    int length = work_print_str.length();
      if (!(work_print_str[length - 1].isDigit() || work_print_str[length - 1] == ')')) {
        work_back_str.push_back("0");
      }
  }
}

void MainWindow::s21_insert_zero() {
  if (!work_print_str.isEmpty()) {
    int length = work_print_str.length();
    if (work_print_str[length - 1] == '.') {
      work_back_str.push_back("0");
      work_print_str.push_back("0");
    }
  }
}

int MainWindow::s21_is_func(QString workString) {
  return workString == "sin" || workString == "cos" || workString == "acos"
  || workString == "asin" || workString == "tan" || workString == "atan"
  || workString == "log" || workString == "ln" || workString == "sqrt";
}

void MainWindow::s21_set_mul(QString str) {
  if (!work_print_str.isEmpty()) {
    int length = work_print_str.length();
    int sign = (work_print_str[length - 1] == '+' || work_print_str[length - 1] == '-'
      || work_print_str[length - 1] == '*' || work_print_str[length - 1]== 'd'
      || work_print_str[length - 1] == '/' || work_print_str[length - 1] == '^'
      || work_print_str[length - 1] == '(' || work_print_str[length - 1] == 'X');
    int sign_2 = (str == "+" || str == "-" || str == "*" || str == "mod"
                             || str == "/" || str == "^" || str == ")");
    if (!sign && !sign_2) {
      work_print_str.push_back(" * ");
      work_back_str.push_back(" * ");
    }
  }
}

void MainWindow::check_func(QString workString) {
  int one_x = 1;
  if (!work_print_str.isEmpty()) {
    int length = work_print_str.length();
    if (work_print_str[length - 1] == 'X') {
        one_x = 0;
    }
  }
  if (s21_is_func(workString)) {
      s21_insert_zero();
      s21_set_mul(workString);
      work_print_str.push_back(workString + "(");
      work_back_str.push_back(workString + " ( ");
      check_dot = 0;
  } else if (workString == "+" || workString == "-" || workString == "*" || workString == "mod"
          || workString == "/" || workString == "(" || workString == ")" || workString == "^") {
      s21_insert_zero();
      if (!work_print_str.isEmpty()) {
        int lenght_1 = work_print_str.length();
        if ((work_print_str[lenght_1 - 1] == '+' || work_print_str[lenght_1 - 1] == '-'
          ||work_print_str[lenght_1 - 1] == '*' || work_print_str[lenght_1 - 1] == 'd'
          || work_print_str[lenght_1 - 1] == '^'|| work_print_str[lenght_1 - 1] == '/')
          && workString != "(" && workString != ")") {
          on_pushButton_del_symb_clicked();
        }
      }
      if (workString == "+" || workString == "-") {
          check_unary();
      }
      s21_set_mul(workString);
      work_print_str.push_back(workString);
      work_back_str.push_back(" " + workString + " ");
      check_dot = 0;
  } else if (workString == "." && check_dot == 0) {
      if (work_print_str.isEmpty()) {
          work_back_str.push_back("0");
          work_print_str.push_back("0");
      } else {
        int lenght = work_print_str.length();
        if (!(work_print_str[lenght - 1].isDigit())) {
          s21_set_mul(workString);
          work_back_str.push_back("0");
          work_print_str.push_back("0");
         }
      }
       work_print_str.push_back(workString);
       work_back_str.push_back(workString);
       check_dot = 1;
  } else if (workString == "X") {
      if (one_x) {
          s21_set_mul(workString);
          work_print_str.push_back(workString);
          work_back_str.push_back(workString);
      }
      is_X = 1;
  } else {
      if (workString != ".") {
          work_print_str.push_back(workString);
          work_back_str.push_back(workString);
      }
  }
}

void MainWindow::PlotGrath(char* result) {
    double ymax = ui->doubleSpinBox_ymax->value();
    double xmax = ui->doubleSpinBox_xmax->value();
    double step = ui->doubleSpinBox_x->value();
    if (ymax == 0) {
        ymax = 20.0;
    }
    if (xmax == 0) {
        xmax = 20.0;
    }
    if (step == 0) {
        step = 0.01;
    }
    for (double X = -xmax; X <= xmax; X += step) {
        x.push_back(X);
        y.push_back((double)s21_set_graph(result, X));
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->widget->xAxis->setRange(-xmax, xmax);
    ui->widget->yAxis->setRange(-ymax, ymax);
    ui->widget->replot();
    x.clear();
    y.clear();
}

void MainWindow::on_pushButton_equal_clicked() {
    int size = work_print_str.length();
    QByteArray str_temp = work_back_str.toLocal8Bit();
    char* result = str_temp.data();

    QByteArray str_valid = work_print_str.toLocal8Bit();
    char* result_valid = str_valid.data();
    int not_valid = s21_is_not_valid(result_valid);
    if (!not_valid && size < 255) {
        if (is_X) {
          PlotGrath(result);
        } else {
          long double result_value = s21_smart_calc(result);
          QString finish = QString::number(result_value, 'g', 10);
          ui->label_result->setText(finish);
          finish.clear();
        }
    } else {
        if (!work_back_str.isEmpty() && !work_print_str.isEmpty()) {
            work_back_str.clear();
            work_print_str.clear();
            ui->label_result->clear();
            ui->label_expression->clear();
        }
        check_dot = 0;
        ui->label_result->setText("Syntax error. Try again");
    }
    is_X = 0;
    work_print_str.clear();
    work_back_str.clear();
}
