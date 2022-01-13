#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include "solution.h"

namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = nullptr);
    MainWindow2(QString* a,myvect* b,article_node* c,int d,int* e,QWidget *parent = nullptr);
    ~MainWindow2();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow2 *ui;
    QString* x;
    myvect* y;
    article_node* z;
    int numbers;
    int* merge;
};

#endif // MAINWINDOW2_H
