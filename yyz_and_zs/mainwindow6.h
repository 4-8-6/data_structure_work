#ifndef MAINWINDOW6_H
#define MAINWINDOW6_H

#include <QMainWindow>
#include "solution.h"

namespace Ui {
class MainWindow6;
}

class MainWindow6 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow6(QWidget *parent = nullptr);
    MainWindow6(QString* a,myvect* b,article_node* c,int d,int* e,QWidget *parent = nullptr);
    ~MainWindow6();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow6 *ui;
    QString* x;
    myvect* y;
    article_node* z;
    int numbers;
    int* merge;
};

#endif // MAINWINDOW6_H
