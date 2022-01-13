#include "mainwindow4.h"
#include "ui_mainwindow4.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow4::MainWindow4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow4)
{
    ui->setupUi(this);
}

MainWindow4::MainWindow4(QString* a,myvect* b,article_node* c,int d,int* e,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow4)
{
    ui->setupUi(this);
    x=a;
    y=b;
    z=c;
    numbers=d;
    merge=e;
}

MainWindow4::~MainWindow4()
{
    delete ui;
}

void MainWindow4::on_pushButton_2_clicked()
{
    MainWindow* test=new MainWindow(x,y,z,numbers,merge);
    test->show();
    this->close();
}

void MainWindow4::on_pushButton_clicked()
{
    QString yz;
    QString text=ui->lineEdit->text();    //获取文本
    yz = year_select(z,text.toInt(),numbers);
    ui->textBrowser->setText(yz);      //输出
}
