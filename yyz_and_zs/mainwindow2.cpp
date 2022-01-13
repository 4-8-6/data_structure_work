#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

MainWindow2::MainWindow2(QString* a,myvect* b,article_node* c,int d,int* e,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    x=a;
    y=b;
    z=c;
    numbers=d;
    merge=e;
}

void MainWindow2::on_pushButton_clicked()
{
    QString text=ui->lineEdit->text();    //获取作者名
    QString yz;
    yz=related_search(x,y,z,text);     //查找与该作者有合作关系的其他作者
    ui->textBrowser->setText(yz);      //输出
}

void MainWindow2::on_pushButton_2_clicked()
{
    MainWindow* test=new MainWindow(x,y,z,numbers,merge);//返回主界面
    test->show();
    this->close();//关闭当前界面
}
