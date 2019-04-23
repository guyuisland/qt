#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QDebug>
#include <string>

#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QString>
#include <QMessageBox>

#include <QDate>
#include <QTime>
#include <QDateTimeEdit>
#include <QTimer>
#include <QThread>
#include <QKeyEvent>
#include <QEvent>

#include <QPixmap>
#include <QScrollArea>
#include <QPalette>
#include <QLayout>
#include <QPalette>

#include<vector>
#include"demand.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //主算法所用变量
    int strategy;
    int start;
    int destination;
    std::string TravelerName;
    std::string TimeBudget;
    std::string TravelerNumber;

    //时间进程变量
    QTimer *mstimer;
    QThread *timethread;

    bool throughcity[12];//途经城市是否被选定的布尔型数组

    void initUI();
    void initConnect();
    void getTravelerName();//获取旅客名称
    int getStart();//获取用户所选始发地
    int getDestination();//获取用户所选目的地
    int getStrategy();//获取用户所选策略
    void getThroughCity();//得到途经城市
    int getTimeRange_Start();//获取出发时间范围_开始
    int getTimeRange_End();//获取出发时间范围_结束
    int getAmPm_1();//获取早上/下午
    int getAmPm_2();//获取早上/下午

    void printout(std::vector<imfo> path);
    void enTimeBudget_Input();//根据旅行模式修改时间预算是否可填
    void getTimeBudget();//获取时间预算
    void showTravelerNumber();//显示旅客编号
    void showTotalTime();//显示方案所需总时间
    void showTotalFare();//显示方案所需经费
    void showTravelPath();//输出旅行路线
    void getTravelerNumber();//获取旅客编号
    void showCurrentTime();//显示当前时间
    void showCurrentLocation();//显示旅客当前所处地点
    void showCurrentState();//显示旅客当前状态/乘坐交通工具

private slots:
    void on_City0_stateChanged(int arg1);
signals:
    void DoStartTimer();//开始计时信号
private slots:
    void on_addTraveler_Click_clicked();//点击添加旅客
    void on_creatTravelPath_Click_clicked();//点击生成旅行路线
    void on_resetTravelerInfo_clicked();//点击重置旅客信息
    void on_startQuery_Click_clicked();//点击开始查询旅客信息
    void on_Mode_Select_currentIndexChanged(int index);//根据旅行模式决定时间预算是否可填
    //设置各个城市是否被选为途经城市
    void on_City1_stateChanged(int arg1);
    void on_City2_stateChanged(int arg1);
    void on_City3_stateChanged(int arg1);
    void on_City4_stateChanged(int arg1);
    void on_City5_stateChanged(int arg1);
    void on_City6_stateChanged(int arg1);
    void on_City7_stateChanged(int arg1);
    void on_City8_stateChanged(int arg1);
    void on_City9_stateChanged(int arg1);
    void on_City10_stateChanged(int arg1);
    void on_City11_stateChanged(int arg1);
};

#endif // MAINWINDOW_H
