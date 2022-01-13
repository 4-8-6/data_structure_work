#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include "mainwindow3.h"
#include "ui_mainwindow3.h"
#include "mainwindow4.h"
#include "ui_mainwindow4.h"
#include "mainwindow5.h"
#include "ui_mainwindow5.h"
#include "mainwindow6.h"
#include "ui_mainwindow6.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置鼠标图案，当鼠标移动到按钮上会变化
    ui->pushButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_3->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_4->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_5->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_6->setCursor(QCursor(Qt::PointingHandCursor));
}

MainWindow::MainWindow(QString* a,myvect* b,article_node* c,int d,int* e,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置鼠标图案，当鼠标移动到按钮上会变化
    ui->pushButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_3->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_4->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_5->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_6->setCursor(QCursor(Qt::PointingHandCursor));
    x=a;
    y=b;
    z=c;
    numbers=d;
    merge=e;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    MainWindow6* test=new MainWindow6(x,y,z,numbers,merge);//创建简介子界面
    test->show();
    this->close();//主界面关闭
}

void MainWindow::on_pushButton_2_clicked()
{
    MainWindow1* test=new MainWindow1(x,y,z,numbers,merge);//创建基本搜索子界面
    test->show();
    this->close();//主界面关闭
}

void MainWindow::on_pushButton_3_clicked()
{
    MainWindow2* test=new MainWindow2(x,y,z,numbers,merge);//创建相关搜索子界面
    test->show();
    this->close();//主界面关闭
}

void MainWindow::on_pushButton_4_clicked()
{
    MainWindow3* test=new MainWindow3(x,y,z,numbers,merge);//创建作者统计子界面
    test->show();
    this->close();//主界面关闭
}

void MainWindow::on_pushButton_5_clicked()
{
    MainWindow4* test=new MainWindow4(x,y,z,numbers,merge);//创建热点分析子界面
    test->show();
    this->close();//主界面关闭
}

void MainWindow::on_pushButton_6_clicked()
{
    MainWindow5* test=new MainWindow5(x,y,z,numbers,merge);//创建部分匹配子界面
    test->show();
    this->close();//主界面关闭
}
