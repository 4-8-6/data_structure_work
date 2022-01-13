#include "mainwindow5.h"
#include "ui_mainwindow5.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow5::MainWindow5(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow5)
{
    ui->setupUi(this);
}

MainWindow5::MainWindow5(QString* a,myvect* b,article_node* c,int d,int* e,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow5)
{
    ui->setupUi(this);
    x=a;
    y=b;
    z=c;
    numbers=d;
    merge=e;
}

MainWindow5::~MainWindow5()
{
    delete ui;
}

void MainWindow5::on_pushButton_4_clicked()
{
    MainWindow* test=new MainWindow(x,y,z,numbers,merge);
    test->show();
    this->close();
}

void MainWindow5::on_pushButton_clicked()
{
    QString yz;
    QString text=ui->lineEdit->text();    //获取文本
    yz+=partselect(z,numbers,text);
    ui->textBrowser->setText(yz);      //输出
}
