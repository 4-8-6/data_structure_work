#ifndef MAINWINDOW5_H
#define MAINWINDOW5_H

#include <QMainWindow>
#include "solution.h"

namespace Ui {
class MainWindow5;
}

class MainWindow5 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow5(QWidget *parent = nullptr);
    MainWindow5(QString* a,myvect* b,article_node* c,int d,int* e,QWidget *parent = nullptr);
    ~MainWindow5();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow5 *ui;
    QString* x;
    myvect* y;
    article_node* z;
    int numbers;
    int* merge;
};

#endif // MAINWINDOW5_H
