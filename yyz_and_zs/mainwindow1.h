#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QMainWindow>
#include "solution.h"

namespace Ui {
class MainWindow1;
}

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = nullptr);
    MainWindow1(QString* a,myvect* b,article_node* c,int d,int* e,QWidget *parent = nullptr);
    ~MainWindow1();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow1 *ui;
    QString* x;
    myvect* y;
    article_node* z;
    int numbers;
    int* merge;
};

#endif // MAINWINDOW1_H
