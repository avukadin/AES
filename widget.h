#ifndef WIDGET_H
#define WIDGET_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<bitset>
#include<QDebug>
#include "source_matrix.h"
#include "key_matrix.h"
#include <QWidget>
#include<QDir>

using namespace std;


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void s_box(char *a);
    void XOR(vector<char> *key_matrix, vector<char> *master_matrix);
    void s_box_inv(char *a);
    vector <char> round_const(int round);
    ~Widget();

private slots:




    void on_pushButton_clicked();



    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    QDir myDir;
    QString Source_path,Password,Dest_path;
    int encrypt;



};

#endif // WIDGET_H
