#include "mainwindow3.h"
#include "ui_mainwindow3.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow3::MainWindow3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow3)
{
    ui->setupUi(this);
}

MainWindow3::MainWindow3(QString* a,myvect* b,article_node* c,int d,int* e,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow3)
{
    ui->setupUi(this);
    x=a;
    y=b;
    z=c;
    numbers=d;
    merge=e;
}

MainWindow3::~MainWindow3()
{
    delete ui;
}

void MainWindow3::on_pushButton_2_clicked()
{
    MainWindow* test=new MainWindow(x,y,z,numbers,merge);
    test->show();
    this->close();
}

void MainWindow3::on_pushButton_clicked()
{
    QString yz;
    yz=find_most_authors(y,x);
    ui->textBrowser->setText(yz);
}
