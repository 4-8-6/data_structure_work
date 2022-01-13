#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow1::MainWindow1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow1)
{
    ui->setupUi(this);
}

MainWindow1::MainWindow1(QString* a,myvect* b,article_node* c,int d,int* e,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow1)
{
    ui->setupUi(this);
    x=a;
    y=b;
    z=c;
    numbers=d;
    merge=e;
}

MainWindow1::~MainWindow1()
{
    delete ui;
}

void MainWindow1::on_pushButton_clicked()
{

    QString text=ui->lineEdit->text();    //获取作者名
    text=use_author_to_search(x,z,text,y);//查找该作者写的文章
    ui->textBrowser->setText(text);      //输出
}

void MainWindow1::on_pushButton_2_clicked()
{
    MainWindow* test=new MainWindow(x,y,z,numbers,merge);//返回主界面
    test->show();
    this->close();//关闭当前界面
}

void MainWindow1::on_pushButton_4_clicked()
{
    QString yz;
    QString text=ui->lineEdit->text();    //获取论文名
    article_node* k = bin_search(z,text,x,merge,0,numbers-1);//利用二分查找查询论文信息
        if(k == nullptr)
        {
            yz+="This article can't be found!\nPlease check the button you pressed or your input.";
        }
        else
        {
                yz+= k->readall();
        }
     ui->textBrowser->setText(yz);//输出
}
