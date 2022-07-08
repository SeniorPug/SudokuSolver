#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<iostream>
#include<algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void SingleElimination(int field[9][9], QString possibleSpots[9][9]){
    bool check;
    do {
        check = false;
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                if (possibleSpots[i][j].size() < 2){
                    for (int x = 0; x < 9; x++){
                        if(possibleSpots[i][x].contains(possibleSpots[i][j]) && x != j){
                            QString str = possibleSpots[i][x];
                            str.remove(possibleSpots[i][j]);
                            possibleSpots[i][x] = str;
                            check = true;
                        }
                    }
                    for (int x = 0; x < 9; x++){
                        if(possibleSpots[x][j].contains(possibleSpots[i][j]) && x != i){
                            QString str = possibleSpots[x][j];
                            str.remove(possibleSpots[i][j]);
                            possibleSpots[x][j] = str;
                            check = true;
                        }
                    }
                    for (int x = 0; x < 3; x++){
                        for (int y = 0; y < 3; y++){
                            int firstCoord = (i/3*3)+x;
                            int secondCoord = (j/3*3)+y;
                            if(possibleSpots[firstCoord][secondCoord].contains(possibleSpots[i][j]) && firstCoord != i && secondCoord != j){
                                QString str = possibleSpots[(i/3*3)+x][(j/3*3)+y];
                                str.remove(possibleSpots[i][j]);
                                possibleSpots[(i/3*3)+x][(j/3*3)+y] = str;
                                check = true;
                            }
                        }
                    }
                }
            }
        }

    } while(check);
}

void MainWindow::on_solutionButton_clicked()
{
    int field[9][9];
    QString possibleSpots[9][9];

    //GET INPUTS AND SETTING UP
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            field[i][j] = findChild<QLineEdit*>("c" + QString::number(i) + "_" + QString::number(j))->text().toInt();
            if(field[i][j] > 0){
                possibleSpots[i][j] = QString::number(field[i][j]);
            } else {
                possibleSpots[i][j] = "123456789";
            }
        }
    }

    //FIRST CYCLE
    SingleElimination(field, possibleSpots);

    //OUTPUT
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            findChild<QLineEdit*>("c" + QString::number(i) + "_" + QString::number(j))->setText(possibleSpots[i][j]);
        }
    }
}

void MainWindow::on_clearButton_clicked()
{
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            findChild<QLineEdit*>("c" + QString::number(i) + "_" + QString::number(j))->setText("");
        }
    }
}

