#ifndef MAINWINDOW4_H
#define MAINWINDOW4_H

#include <QMainWindow>
#include "solution.h"

namespace Ui {
class MainWindow4;
}

class MainWindow4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow4(QWidget *parent = nullptr);
    MainWindow4(QString* a,myvect* b,article_node* c,int d,int* e,QWidget *parent = nullptr);
    ~MainWindow4();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow4 *ui;
    QString* x;
    myvect* y;
    article_node* z;
    int numbers;
    int* merge;
};

#endif // MAINWINDOW4_H
