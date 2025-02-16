#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>

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
    void sltValueChanged(int value);
    void sltModChange();

private:
    Ui::MainWindow *ui;

    // 初始化界面

    void initDial(void);
    void initLcd(void);
    void initRadioButton(void);

    QButtonGroup buttongroup;

};
#endif // MAINWINDOW_H
