#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define NAMESLIDER 1
#define NAMESCROLLBAR 2
#define NAMEPRAGRESSBAR 3

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置 title
    setWindowTitle(QObject::tr("LaTale: slider scrollbar progressbar 控件联动实验"));

    // 设置信号属性
    ui->horizontalSlider->setProperty("type", NAMESLIDER);
    ui->horizontalScrollBar->setProperty("type", NAMESCROLLBAR);
    ui->progressBar->setProperty("type", NAMEPRAGRESSBAR);

    // 信号与槽绑定
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(sltValueChanged(int)));
    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(sltValueChanged(int)));
    connect(ui->progressBar, SIGNAL(valueChanged(int)), this, SLOT(sltValueChanged(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::sltValueChanged(int value)
{
    Q_UNUSED(value);

    // 获取发送信号
    QObject * object = sender();
    int property = object->property("type").toInt();

    switch(property)
    {
        int value;
        case NAMESLIDER:
        {
            value = ui->horizontalSlider->value();
            qDebug() << "SILIDER " << value;
            changeVerticalValue(value);
            break;
        }
        case NAMESCROLLBAR:
        {
            value = ui->horizontalScrollBar->value();
            qDebug()<< "SCROLLBAR: " << value;
            changeVerticalValue(value);
            break;
        }
        // progressbar 用于显示不可交互
        case NAMEPRAGRESSBAR:
        {
            value = ui->progressBar->value();
            changeVerticalValue(value);
            break;
        }
        default:
        {
            qFatal()<< "signal erro";
            break;
        }
    }

}

// 修改控件的值
void MainWindow::changeVerticalValue(int value)
{
    ui->verticalSlider->setValue(value);
    ui->verticalScrollBar->setValue(value);
    ui->progressBar_2->setValue(value);
}




