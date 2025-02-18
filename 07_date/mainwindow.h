#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sltGetTime();
    void sltBegin();
    void sltStop();
    void sltTime();
    void sltDate();
    void sltDateTime();
    void sltsetTimer();
    void sltSelectChanged();
    void onTimeout();
private:
    Ui::MainWindow *ui;
    QTimer * m_timer;
    QTime m_time;
    int hh;
    int mm;
    int ss;
    int persent1;
    int persent2;

};
#endif // MAINWINDOW_H
