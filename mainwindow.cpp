#include "mainwindow.h"

#include <QPushButton>

#include "myfunction.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  int mWidth = ui->groupBox_Register_Table->size().width() / 16;
  myDebug() << mWidth;
  QSizePolicy mySizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  mySizePolicy.setHorizontalStretch(mWidth);
  mySizePolicy.setVerticalStretch(mWidth);
  QSize mySize(mWidth, mWidth);

  // label_RegisterTable
  for (int i = 31; i >= 0; i--) {
    QLabel *pLabe_RegisterTable =
        new QLabel(tr("%1").arg(i), ui->groupBox_Register_Table);
    //    pLabe_RegisterTable->setObjectName(tr("label_Reg_Bit_%1").arg(i, 2,
    //    10, '0'));

    pLabe_RegisterTable->setSizePolicy(mySizePolicy);
    pLabe_RegisterTable->setMinimumSize(mySize);
    pLabe_RegisterTable->setMaximumSize(mySize);
    pLabe_RegisterTable->setBaseSize(mySize);
    pLabe_RegisterTable->setAutoFillBackground(false);
    pLabe_RegisterTable->setStyleSheet(
        tr("font: 14pt \"Symbol\";background-color: rgb(170, %1, 255);")
            .arg((i % 4) * 85));
    pLabe_RegisterTable->setAlignment(Qt::AlignHCenter | Qt::AlignBaseline);
    if (i / 16) {
      ui->horizontalLayout_Reg_High15bit_label->addWidget(pLabe_RegisterTable);
    } else {
      ui->horizontalLayout_Reg_Low15bit_label->addWidget(pLabe_RegisterTable);
    }
  }

  // btn_RegisterTable

  this->ui->le_RegisterTable_Value->setText(
      QString::number(registerTable.value.to_ullong(), 16));
  registerTable.pbtn_Group = new QButtonGroup;
  registerTable.pbtn_Bit = new QPushButton *[32];

  for (int i = 31; i >= 0; i--) {
    registerTable.pbtn_Bit[i] =
        new QPushButton("0", this->ui->groupBox_Register_Table);
    registerTable.pbtn_Bit[i]->setCheckable(true);
    registerTable.pbtn_Bit[i]->setSizePolicy(mySizePolicy);
    registerTable.pbtn_Bit[i]->setMaximumSize(mySize);
    registerTable.pbtn_Bit[i]->setMinimumSize(mySize);
    registerTable.pbtn_Bit[i]->setIconSize(mySize);
    registerTable.pbtn_Bit[i]->setStyleSheet(tr("font: 14pt \"Symbol\";"));
    if (i / 16) {
      ui->horizontalLayout_Reg_High15bit_btn->addWidget(
          registerTable.pbtn_Bit[i]);
    } else {
      ui->horizontalLayout_Reg_Low15bit_btn->addWidget(
          registerTable.pbtn_Bit[i]);
    }
    registerTable.pbtn_Group->addButton(registerTable.pbtn_Bit[i], i);
  }

  connect(registerTable.pbtn_Group, SIGNAL(buttonClicked(int)), this,
          SLOT(btn_Reg_flip(int)));

  // label_GrayCode
  for (int i = 31; i >= 0; i--) {
    QLabel *pLabe_GrayCode = new QLabel(tr("%1").arg(i), ui->groupBox_GrayCode);
    //    pLabe_GrayCode->setObjectName(tr("label_GrayCode_Bit_%1").arg(i, 2,
    //    10, '0'));

    pLabe_GrayCode->setSizePolicy(mySizePolicy);
    pLabe_GrayCode->setMinimumSize(mySize);
    pLabe_GrayCode->setMaximumSize(mySize);
    pLabe_GrayCode->setBaseSize(mySize);
    pLabe_GrayCode->setAutoFillBackground(false);
    pLabe_GrayCode->setStyleSheet(
        tr("font: 14pt \"Symbol\";background-color: rgb(170, %1, 255);")
            .arg((i % 4) * 85));
    pLabe_GrayCode->setAlignment(Qt::AlignHCenter | Qt::AlignBaseline);
    if (i / 16) {
      ui->horizontalLayout_GrayCode_High15bit_label->addWidget(pLabe_GrayCode);
    } else {
      ui->horizontalLayout_GrayCode_Low15bit_label->addWidget(pLabe_GrayCode);
    }
  }

  // btn_GrayCode

  this->ui->le_GrayCode_Value->setText(
      QString::number(grayCode.value.to_ullong(), 16));
  grayCode.pbtn_Group = new QButtonGroup;
  grayCode.pbtn_Bit = new QPushButton *[32];

  for (int i = 31; i >= 0; i--) {
    grayCode.pbtn_Bit[i] = new QPushButton("0", this->ui->groupBox_GrayCode);
    grayCode.pbtn_Bit[i]->setCheckable(true);
    grayCode.pbtn_Bit[i]->setSizePolicy(mySizePolicy);
    grayCode.pbtn_Bit[i]->setMaximumSize(mySize);
    grayCode.pbtn_Bit[i]->setMinimumSize(mySize);
    grayCode.pbtn_Bit[i]->setIconSize(mySize);
    grayCode.pbtn_Bit[i]->setStyleSheet(tr("font: 14pt \"Symbol\";"));
    if (i / 16) {
      ui->horizontalLayout_GrayCode_High15bit_btn->addWidget(
          grayCode.pbtn_Bit[i]);
    } else {
      ui->horizontalLayout_GrayCode_Low15bit_btn->addWidget(
          grayCode.pbtn_Bit[i]);
    }
    grayCode.pbtn_Group->addButton(grayCode.pbtn_Bit[i], i);
  }

  connect(grayCode.pbtn_Group, SIGNAL(buttonClicked(int)), this,
          SLOT(btn_GrayCode_flip(int)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::btn_Reg_flip(int id) {
  registerTable.value.flip(id);
  ui->le_RegisterTable_Value->setText(
      QString::number(registerTable.value.to_ullong(), 16));
}

void MainWindow::btn_GrayCode_flip(int id) {
  grayCode.value.flip(id);
  ui->le_GrayCode_Value->setText(
      QString::number(grayCode.value.to_ullong(), 16));
}

unsigned long long MainWindow::BinaryToGray(unsigned long long num) {
  return num ^ (num >> 1);
}

unsigned long long MainWindow::GrayToBinary(unsigned long long num) {
  unsigned long long mask = num >> 1;
  while (mask != 0) {
    num = num ^ mask;
    mask = mask >> 1;
  }
  return num;
}
void binaryCode::updateBit() {
  for (unsigned int i = 0; i < 32; i++) {
    if (value[i]) {
      pbtn_Bit[i]->setText("1");
    } else {
      pbtn_Bit[i]->setText("0");
    }
  }
}

void MainWindow::on_le_RegisterTable_Value_textChanged(const QString &arg1) {
  unsigned long long tmpval = arg1.toULongLong(nullptr, 16);
  if (!registerTable.changed) {
    registerTable.changed = 1;
    registerTable.value = tmpval;
    registerTable.updateBit();
    grayCode.value = BinaryToGray(registerTable.value.to_ullong());
    ui->le_GrayCode_Value->setText(
        QString::number(grayCode.value.to_ullong(), 16));
    registerTable.changed = 0;
  }
}

void MainWindow::on_le_GrayCode_Value_textChanged(const QString &arg1) {
  unsigned long long tmpval = arg1.toULongLong(nullptr, 16);
  if (!grayCode.changed) {
    grayCode.changed = 1;
    grayCode.value = tmpval;
    grayCode.updateBit();
    registerTable.value = GrayToBinary(grayCode.value.to_ullong());
    ui->le_RegisterTable_Value->setText(
        QString::number(registerTable.value.to_ullong(), 16));
    grayCode.changed = 0;
  }
}
