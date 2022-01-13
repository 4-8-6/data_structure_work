#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <cmath>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include "XmlStreamReader.h"
using namespace std;

#define hash_len 5000000 //定义宏

//定义3个结构
struct treenode//链表实现二叉树
{
  QString str;
  int number;
  treenode*left;
  treenode*right;
  treenode(QString st)//构造函数
  {
      left = right = nullptr;
      str = st;
      number = 1;
  }
  treenode()//构造函数
  {
      str = "";
      number = 0;
      left = right = nullptr;
  }
  ~treenode()//析构函数
  {
      left = right = nullptr;
  }
  void copy(int a, QString b)//复制树节点
  {
      str = b;
      number = a;
  }
};
struct myvect     //存放同一作者写的所有文章的相关信息
{
    int * poses;//作者写的所有文章的顺序位置
    int len;//作者写的文章的数量
    int max;//一个上界，可扩大
    myvect()//构造函数，对结点初始化
    {
        max = 1;
        len = 0;
        poses = new int[max];//记录顺序位置
    }
    void append(int a)//追加记录
    {
        if(len < max)poses[len++] = a;//检查长度是否超过上界，如果超过了要对max扩大
        else
        {
            max = max * 2;
            int *p = new int[max];
            for(int i = 0 ; i < len;i++)
            {
                p[i] = poses[i];
            }
            p[len++] = a;
            delete[]poses;
            poses = p;
        }
    }

    ~myvect()//析构函数
    {
        delete[]poses;
    }
};
struct article_node//存放一篇文章的所有信息
{
    int pos;//记录顺序位置
    int year;//存放年份
    QString title;//存放文章标题
    int* authors;//存放author的哈希位置
    int len;//文章的作者数
    int max;//一个上界
    int filepos;//记录在data.txt文件中的位置
    article_node()//构造函数
    {
        year = 0;
        title = "";
        authors = new int[2];
        len = 0; max = 2;
    }
    ~article_node()//析构函数
    {
        delete[]authors;
    }
    void set(QString str,QString* all_author,int x,myvect * author_article)//存入一篇文章的信息
    {
        pos = x;
        QStringList lis=str.split("\t");//year,title,authors和pos以"\t"隔开，各author以","隔开
        year = lis[0].toInt();
        title=lis[1];
        QString k = lis[2];
        QStringList lis1 = k.split(',');
        for(int i = 0; i < lis1.size();i++)
        {
            if(lis1[i]!="")
            {
                append(HASH(lis1[i],all_author,author_article));//把信息放进两个哈希表中且存放author的哈希值
            }
        }
        filepos = lis[3].toInt();
    }
    int HASH(QString str,QString* all_author,myvect* author_article)//利用hash和500w大小进行存储
    {
        QByteArray byte = str.toUtf8();
        int64_t sum = 0;
        for(int i = 0; i < str.size();i++)
        {
             sum += abs(int(byte.at(i)))*pow(10,i%8);//按作者的名字计算哈希值
        }
        sum = sum%hash_len;
        int j = 0;
        while(1)
        {

            sum = (sum+int(pow(j,2)))%hash_len;
            if(all_author[sum]=="")//哈希位置为空
            {
                    all_author[sum] = str;
                    author_article[sum].append(pos);
                    return sum;
            }
            else          //哈希位置不为空
            {
                ++j;
                if(str == all_author[sum])//是同一作者
                {
                    author_article[sum].append(pos);
                    return sum;
                }
                else//不是同一作者，寻找下一哈希位置
                {

                }
            }
        }
    }
    void append(int QS)//存放一篇文章所有author的哈希值
    {
        if(len < max){}
        else
        {
            max = max+2;
            int*ptr = new int[max];
            for(int i = 0 ; i < len; i++)
            {
                ptr[i] = authors[i];
            }
            delete[]authors;
            authors = ptr;
        }
        authors[len++] = QS;

    }
    QString show()//获取文章主要信息
    {
        QString x;
        x=title;
        x+="\t";
        x+=QString::number(year);
        return x;
    }
    QString readall()//读取一篇文章的全部内容
    {
        QString yz;
        QFile file(".\\data.txt");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            yz+="Can't open the file!";
        }
            QByteArray line;
            for (int i = 0 ; i < filepos;i++)
            {
                line = file.readLine();//定位到对应的行位置
            }
                QString str(line);
                    if(filepos!=1)yz+=str.mid(10);//开头为</article>,要略去
                    else{
                        yz+=str;//开头为<article>
                    }
                    while(1)//读取一条<article>下的所有内容
                    {
                        QByteArray line = file.readLine();
                        QString str(line);
                        if(str.left(10)=="</article>")//读到结束符号，读取完毕
                        {
                            yz+=str.left(10);
                            break;
                        }
                        else
                        {
                            yz+=str;
                        }

                    }
        file.close();
        XmlStreamReader read;
        yz=read.xmlStreamReaderFile(yz);//对读取出来的xml文本解析
        return yz;
    }
};
struct ACnode
{
  char ch;
  ACnode*fail;
  int len;
  int count;
  ACnode*next[10];
  ACnode()
  {
      len = 0;
      ch = '/';
      fail = nullptr;
      count = 0;
      for(int i = 0 ; i < 10; ++i)
      {
          next[i] = nullptr;
      }
  }
  ACnode(char c)
    {
        len = 0 ;
        ch = c;
        count = 0;
        fail = nullptr;
        for(int i = 0 ; i < 10; ++i)
        {
            next[i] = nullptr;
        }
    }
};

//定义各函数

//完成基本搜索之输入作者名查找其发表的所有论文
QString use_author_to_search(QString*,article_node*,QString,myvect*);      //一个接口函数，用作者找对应文章
QString readsome(int*,int);        //批量读取xml文件,第一个参数是多个pos的数组，第二个是数组长度
int hash_find(QString,QString* );  //计算哈希值

//完成基本搜索之输入文章名查找相关信息
void mergesort(article_node*,int* ,int, int);                           //利用pos和文章标题进行排序
article_node* bin_search(article_node* ,QString, QString*,int *, int, int); //二分查找文章标题（完整题目查找）

//相关搜索
QString related_search(QString*,myvect*,article_node*,QString);//寻找一名作者的合作者

//作者统计
QString find_most_authors(myvect*,QString*);       //找写的最多的作者最多的作者，用myvect存作者写的文章
void quicksort(int*, myvect*,int, int);         //找最多作者里用到的排序

//热点分析
QString year_select(article_node*,int,int);        //对年份进行查找，进行热点分析
void treeappend(treenode*,QString);             //和下面带tree的都一样。目的是建立二叉树进行年度热词盘点
treenode* treefind(treenode*,QString);
void tree_delete(treenode*);
void treeshow(treenode* ,treenode* ,int*);
void treeswap(treenode*,int ,int);
void heapturn(treenode*,int);
QString heapshow(treenode*,int,int);

//部分匹配
QString partselect(article_node*,int,QString);//部分查找
int judge_string(QString& match_str);         //剔除一些词、长度小于2的串以及标点符号，和上面进行配合
bool ACinsert(QString, ACnode*,int);
bool buildfail(ACnode*);
bool ACsearch(QString,ACnode*,int);
void ACtrash(ACnode*);

#endif // SOLUTION_H
