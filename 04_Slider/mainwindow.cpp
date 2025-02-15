#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QColor>
#include <QPalette>
#include <QSlider>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("LaTale: QSlider实验"));

    // 初始化 linedit 背景颜色
    QColor color;
    color.setRgb(100, 100, 100, 255);
    // 获取 textedit 背景颜色
    QPalette palette = ui->textEdit->palette();
    palette.setColor(QPalette::Base, color);
    ui->textEdit->setPalette(palette);

    // 设置滑条最大值
    ui->horizontalSlider_red->setMaximum(255);
    ui->horizontalSlider_green->setMaximum(255);
    ui->horizontalSlider_blue->setMaximum(255);
    ui->horizontalSlider_alpha->setMaximum(255);

    // 信号与槽设置
    connect(ui->horizontalSlider_red, SIGNAL(valueChanged(int)), this, SLOT(sltValueChanged(int)));
    connect(ui->horizontalSlider_green, SIGNAL(valueChanged(int)), this, SLOT(sltValueChanged(int)));
    connect(ui->horizontalSlider_blue, SIGNAL(valueChanged(int)), this, SLOT(sltValueChanged(int)));
    connect(ui->horizontalSlider_alpha, SIGNAL(valueChanged(int)), this, SLOT(sltValueChanged(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 槽函数 当滑条值发生触发时启用
void MainWindow::sltValueChanged(int value)
{
    Q_UNUSED(value);

    // 获取四个滑动条的值
    int red = ui->horizontalSlider_red->value();
    int green = ui->horizontalSlider_green->value();
    int blue = ui->horizontalSlider_blue->value();
    int alpha = ui->horizontalSlider_alpha->value();

    qDebug() << "rgb: " << red << " " << green << " " << blue << " " << alpha;

    QColor color;
    color.setRgb(red, green, blue, alpha);
    QPalette palette = ui->textEdit->palette();
    palette.setColor(QPalette::Base, color);
    ui->textEdit->setPalette(palette);
}
