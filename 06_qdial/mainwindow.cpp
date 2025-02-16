#include "mainwindow.h"
#include "./ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , buttongroup(new QButtonGroup(this))
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("LaTale: QDial 显示实验"));

    initDial();
    initLcd();
    initRadioButton();

    // 信号和槽
    connect(ui->dial, SIGNAL(valueChanged(int)), this, SLOT(sltValueChanged(int)));
    connect(ui->radioButton_2, SIGNAL(clicked()), this, SLOT(sltModChange()));
    connect(ui->radioButton_8, SIGNAL(clicked()), this, SLOT(sltModChange()));
    connect(ui->radioButton_10, SIGNAL(clicked()), this, SLOT(sltModChange()));
    connect(ui->radioButton_16, SIGNAL(clicked()), this, SLOT(sltModChange()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

// 初始化 dial
void MainWindow::initDial(void)
{
    ui->dial->setRange(0, 359);
    ui->dial->setWrapping(true);
    ui->dial->setNotchesVisible(true);
    ui->dial->setSingleStep(1);
}

// 初始化 lcd
void MainWindow::initLcd(void)
{
    ui->lcdNumber->display(0);
    // 二进制显示
    ui->lcdNumber->setDecMode();
    ui->lcdNumber->setDigitCount(10);
}

// 初始化 radiobutton
void MainWindow::initRadioButton(void)
{
    ui->radioButton_10->setChecked(true);
    buttongroup.addButton(ui->radioButton_2, 1);
    buttongroup.addButton(ui->radioButton_8, 2);
    buttongroup.addButton(ui->radioButton_10, 3);
    buttongroup.addButton(ui->radioButton_16, 4);
    buttongroup.setExclusive(true);
}


void MainWindow::sltValueChanged(int value)
{
    Q_UNUSED(value);
    int nValue = ui->dial->value();
    ui->lcdNumber->display(nValue);
}

void MainWindow::sltModChange()
{
    if(ui->radioButton_2->isChecked())
    {
        ui->lcdNumber->setBinMode();
        qDebug() << "2 进制模式"<<QString::number(ui->dial->value(), 2);
    }

    if(ui->radioButton_8->isChecked())
    {
        ui->lcdNumber->setOctMode();
        qDebug() << "8 进制模式"<<QString::number(ui->dial->value(), 8);
    }

    if(ui->radioButton_10->isChecked())
    {
        ui->lcdNumber->setDecMode();
        qDebug() << "10 进制模式"<< QString::number(ui->dial->value(), 10);
    }

    if(ui->radioButton_16->isChecked())
    {
        ui->lcdNumber->setHexMode();
        qDebug() << "16 进制模式: "<< QString::number(ui->dial->value(), 16);
    }



}


