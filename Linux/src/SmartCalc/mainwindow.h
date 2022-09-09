#ifndef SRC_SMARTCALC_MAINWINDOW_H_
#define SRC_SMARTCALC_MAINWINDOW_H_

#include <QMainWindow>
#include <QVector>

extern "C" {
  #include "s21_smart_calc.h"
}

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; } QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  void PlotGrath();
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  QString work_print_str;
  QString work_back_str;
  int check_dot = 0;
  int is_X = 0;
  QVector<double> x;
  QVector<double> y;

 private slots:
  void digits_numbers();
  void on_pushButton_del_all_clicked();
  void check_func(QString workString);
  void check_unary();
  void on_pushButton_equal_clicked();
  void s21_insert_zero();
  void on_pushButton_del_symb_clicked();
  void PlotGrath(char* result);
  int s21_is_func(QString workString);
  void s21_set_mul(QString str);
};


#endif  //  SRC_SMARTCALC_MAINWINDOW_H_
