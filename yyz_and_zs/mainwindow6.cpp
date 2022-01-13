#include "mainwindow6.h"
#include "ui_mainwindow6.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow6::MainWindow6(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow6)
{
    ui->setupUi(this);
}

MainWindow6::MainWindow6(QString* a,myvect* b,article_node* c,int d,int* e,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow6)
{
    ui->setupUi(this);
    x=a;
    y=b;
    z=c;
    numbers=d;
    merge=e;
}

MainWindow6::~MainWindow6()
{
    delete ui;
}

void MainWindow6::on_pushButton_clicked()
{
    MainWindow* test=new MainWindow(x,y,z,numbers,merge);
    test->show();
    this->close();
}
