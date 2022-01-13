#ifndef MAINWINDOW3_H
#define MAINWINDOW3_H

#include <QMainWindow>
#include "solution.h"

namespace Ui {
class MainWindow3;
}

class MainWindow3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow3(QWidget *parent = nullptr);
    MainWindow3(QString* a,myvect* b,article_node* c,int d,int* e,QWidget *parent = nullptr);
    ~MainWindow3();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow3 *ui;
    QString* x;
    myvect* y;
    article_node* z;
    int numbers;
    int* merge;
};

#endif // MAINWINDOW3_H
