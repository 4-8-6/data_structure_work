#include "mainwindow.h"
#include "solution.h"
#include <QApplication>

//定义三个结构体存储数据
QString* all_author = new QString[hash_len];//全体作者的哈希表，只存储作者名字
myvect* author_article = new myvect[hash_len];//全体作者对应他写的文章的哈希表（会存储article对应library的pos值）
article_node* libarary = new article_node[3000000];//文章，存储文章的主要信息，包括一个可以读取文章详细信息的位置
//all_author 和 author_artible中同一位置对应同一作者

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);//调整编码，使中文可以正常在mainwindow窗口显示
    QApplication a(argc, argv);
//    system("cd");

    //读取文件
    QFile file(".\\author.txt");//打开author文件
    int numbers = 0;//记录的条数
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           qDebug()<<"Can't open the file!";
       }
    while(!file.atEnd())
       {
           QByteArray line = file.readLine();
           //author中一条记录存一行，格式为：year,title,authors，pos以"\t"隔开，各author以","隔开
           QString str(line);
           libarary[numbers].set(str,all_author,numbers,author_article);
           numbers++;
           if(numbers%10000==0) qDebug()<<numbers;
           //if(numbers==200000)break;//因测试时间太久，所以只用一部分数据
        }
    qDebug()<<numbers;
    file.close();

    //首先merged建立一个与pos值对应的int数组，然后使用mergesort函数对int数组进行排序,便于查找
    int* merged = new int[numbers];
    for(int i = 0;i < numbers; i++)
        {
                merged[i] = i;
        }
    mergesort(libarary,merged, 0 , numbers-1);

    //建立并打开主窗口
    MainWindow w(all_author,author_article,libarary,numbers,merged);
    w.show();

    return a.exec();
}
