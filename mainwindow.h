#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QButtonGroup>
#include <QLabel>
#include <bits/stdc++.h>

using namespace std;

namespace Ui {
  class MainWindow;
}


struct binaryCode{
  unsigned int changed = 0;
  bitset<32> value;
  QButtonGroup *pbtn_Group;
  QPushButton **pbtn_Bit;
  void updateBit();
};

class MainWindow : public QMainWindow
{
  Q_OBJECT


public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  binaryCode registerTable, grayCode;

private slots:
  void btn_GrayCode_flip(int id);
  void btn_Reg_flip(int id);
  void on_le_RegisterTable_Value_textChanged(const QString &arg1);
  void on_le_GrayCode_Value_textChanged(const QString &arg1);

private:
  Ui::MainWindow *ui;

  unsigned long long BinaryToGray(unsigned long long num);
  unsigned long long GrayToBinary(unsigned long long num);
};

#endif // MAINWINDOW_H
