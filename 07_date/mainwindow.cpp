#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    // 1000 ms
    m_timer->setInterval(1000);
    m_timer->stop();

    ui->progressBar_timer->setMinimum(0);  // 设置最小值为 0
    ui->progressBar_timer->setMaximum(100);  // 设置最大值为 100

    // 初始化 日历
    ui->calendarWidget->setSelectedDate(QDate::currentDate());
    ui->lineEdit_showDate->setText(QDate::currentDate().toString("yyyy-MM-dd"));

    // 获取当前时间
    QDateTime currentDateTime = QDateTime::currentDateTime();
    ui->label_showDateTime->setText(currentDateTime.toString("yyyy-MM-dd  hh:mm:ss"));

    ui->timeEdit->setTime(currentDateTime.time());
    ui->lineEdit->setText(currentDateTime.toString("hh:mm:ss"));

    ui->dateEdit->setDate(currentDateTime.date());
    ui->lineEdit_2->setText(currentDateTime.toString("yyyy-MM-dd"));

    ui->dateTimeEdit->setDateTime(currentDateTime.currentDateTime());
    ui->lineEdit_3->setText(currentDateTime.toString("yyyy-MM-dd : hh:mm:ss"));


    // 信号与槽 两种写法
    connect(ui->pushButton_getTime, SIGNAL(clicked()), this, SLOT(sltGetTime())); // 旧
    connect(ui->timeEdit, &QTimeEdit::timeChanged, this, &MainWindow::sltTime); // 新
    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &MainWindow::sltDate);
    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &MainWindow::sltDateTime);

    // 点击设置周期
    connect(ui->pushButton_period, &QPushButton::clicked, this, &MainWindow::sltsetTimer);
    // 开始
    connect(ui->pushButton_begin, &QPushButton::clicked, this, &MainWindow::sltBegin);
    // 停止
    connect(ui->pushButton_stop, &QPushButton::clicked, this, &MainWindow::sltStop);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::onTimeout);

    connect(ui->calendarWidget, SIGNAL(selectionChanged()),this, SLOT(sltSelectChanged()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 1s 触发一次
void MainWindow::onTimeout()
{
    // 更新 lcd
    ui->lcdNumber_h->display(hh);
    ui->lcdNumber_m->display(mm);
    ui->lcdNumber_s->display(ss);

    qDebug() << hh << ":" << mm << ":" << ss;
    qDebug() << persent2 << "/" << persent1;

    // 更新进度条
    persent2++;
    ui->progressBar_timer->setValue(persent2 * 100 / persent1);

    ss--;
    if(ss<0 && mm>0)
    {
        ss = 59;
        mm--;
    }
    if(mm<0 && hh>0)
    {
        hh--;
    }
    if(hh==0 && mm ==0 && ss<0)
    {
        // 这里可以优化，简单方案发射一个停止信号 pushButton_stop
        emit ui->pushButton_stop->clicked();  // 触发 clicked 信号
        return;
    }

}


void MainWindow::sltBegin()
{
    m_timer->start();
    ui->pushButton_begin->setEnabled(false);
    ui->pushButton_stop->setEnabled(true);
    ui->timeEdit_inputTimer->setEnabled(false);
    ui->label_5->setText("正在倒计时 。。。");
    ui->progressBar_timer->setValue(0);

}

void MainWindow::sltStop()
{
    m_timer->stop();
    ui->pushButton_begin->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);
    ui->timeEdit_inputTimer->setEnabled(true);
    ui->label_5->setText("");
}

void MainWindow::sltGetTime()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    ui->label_showDateTime->setText(currentDateTime.toString("yyyy-MM-dd  hh : mm : ss"));

    ui->timeEdit->setTime(currentDateTime.time());
    ui->lineEdit->setText(currentDateTime.toString("hh : mm : ss"));

    ui->dateEdit->setDate(currentDateTime.date());
    ui->lineEdit_2->setText(currentDateTime.toString("yyyy-MM-dd"));

    ui->dateTimeEdit->setDateTime(currentDateTime.currentDateTime());
    ui->lineEdit_3->setText(currentDateTime.toString("yyyy-MM-dd  hh : mm : ss"));

}

void MainWindow::sltTime()
{
    QTime qtime = ui->timeEdit->time();
    ui->lineEdit->setText(qtime.toString("hh : mm : ss"));

}

void MainWindow::sltDate()
{
    QDate qdate = ui->dateEdit->date();
    ui->lineEdit_2->setText(qdate.toString("yyyy-MM-dd"));
}


void MainWindow::sltDateTime()
{
    QDateTime qdateTime = ui->dateTimeEdit->dateTime();
    ui->lineEdit_3->setText(qdateTime.toString("yyyy-MM-dd hh:mm:ss"));
}

void MainWindow::sltSelectChanged()
{
    ui->lineEdit_showDate->setText(ui->calendarWidget->selectedDate()
                                       .toString("yyyy-MM-dd"));
}


void MainWindow::sltsetTimer()
{
    // 获取设置值
    m_time = ui->timeEdit_inputTimer->time();
    hh = m_time.hour();
    mm = m_time.minute();
    ss = m_time.second();

    persent1 = m_time.hour()*3600 + m_time.minute()*60 + m_time.second();
    persent2 = 0;
    qDebug() << m_time.hour()<<":"<<m_time.minute()<<":"<<m_time.second();
}



