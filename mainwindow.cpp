#include "mainwindow.h"
#include "board.h"
#include "./ui_mainwindow.h"
#include "enemy.h"
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // init table
    for(int i = 0; i<b.getSize(); i++){
        table.push_back(vector<int>(b.getSize(),0));
    }

    e = Enemy(table);

    b = Board(*ui->tableWidget);

    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &MainWindow::onCellClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCellClicked(int x, int y){

    if(ui->tableWidget->item(x,y) == NULL || ui->tableWidget->item(x,y)->text() == ""){ // Only if it is empty

        ui->tableWidget->setItem(x, y, new QTableWidgetItem("x"));

        ui->tableWidget->item(x,y)->setTextAlignment(Qt::AlignCenter);

        table[x][y] = 1; // x

        pair<int, int> point = e.check();
        int t = point.first;
        int z = point.second;

        if(t != -1){

            ui->tableWidget->setItem(t, z, new QTableWidgetItem("o"));
            ui->tableWidget->item(t,z)->setTextAlignment(Qt::AlignCenter);

            table[t][z] = 2; // o

        }

        // check if won
        vector<pair<int, int>> victory = checkIfWon();

        // Check if all cells are taken
        bool allTaken = true;
        for(int i = 0; i<b.getSize(); i++){

            if(allTaken == false){
                break;
            }

            for(int j = 0; j<b.getSize(); j++){
                if(table[i][j] == 0){
                    allTaken = false;
                    break;
                }
            }
        }

        if(allTaken && !userWon && !enemyWon){
            ui->tableWidget->item(x,y)->setSelected(false);
            ui->tableWidget->setEnabled(false);
            QMessageBox msg = QMessageBox();

            msg.setWindowTitle("Result");
            msg.setStyleSheet("QMessageBox{background-color: black;} "
                              "QLabel{min-width: 180px; font-size: 50px; color: red; text-align: center;} "
                              "QPushButton{width: 25px; font-size: 30px; background-color: red;}");


            msg.setText("Draw!");
            msg.exec();
        }


        if(userWon || enemyWon){
            ui->tableWidget->setEnabled(false);
            QMessageBox msg = QMessageBox();

            msg.setWindowTitle("Result");
            msg.setStyleSheet("QMessageBox{background-color: black;} "
                              "QLabel{min-width: 180px; font-size: 50px; color: red; text-align: center;} "
                              "QPushButton{width: 25px; font-size: 30px; background-color: red;}");


            if(userWon){
                msg.setText("Victory!!");
            }else{
                msg.setText("Defeat.");
            }

            // draw cells for the victory
            for(auto p : victory){
                ui->tableWidget->item(p.first, p.second)->setSelected(true);
            }
            if(!userWon)
                ui->tableWidget->item(x,y)->setSelected(false);

            msg.exec();
        }
    }else{ // Not empty
        QMessageBox msg = QMessageBox();

        msg.setWindowTitle("Warning");
        msg.setStyleSheet("QMessageBox{background-color: black;} "
                          "QLabel{min-width: 500px; font-size: 50px; color: red; text-align: center;} "
                          "QPushButton{width: 25px; font-size: 30px; background-color: red;}");
        msg.setText("This cell is not empty, choose another one!");
        msg.exec();
    }


}
vector<pair<int, int>> MainWindow::checkIfWon(){
    // check if the game has been won

    vector<pair<int,int>> w1 = e.checkWon(1);
    vector<pair<int,int>> w2 = e.checkWon(2);

    for(int i = 0; i < w1.size(); i++){
        userWon = true;
        if(w1[i].first == -1){
            userWon = false;
            break;
        }
    }
    for(int i = 0; i < w2.size(); i++){
        enemyWon = true;
        if(w2[i].first == -1){
            enemyWon = false;
            break;
        }
    }
    if(userWon){
        return w1;
    }
    else if(enemyWon){
        return w2;
    }

    vector<pair<int, int>> v(1, make_pair(-1,-1));

    return v;
}

void MainWindow::on_buttonReset_clicked()
{
    // reset vars
    userWon = false;
    enemyWon = false;

    // reset the table
    for(int i = 0; i<b.getSize(); i++){
        for(int j = 0; j<b.getSize(); j++){
            table[i][j] = 0;
            ui->tableWidget->setItem(i,j, new QTableWidgetItem(""));
        }
    }
    // deselect items
    for(auto item : ui->tableWidget->selectedItems()){
        item->setSelected(false);
    }
    ui->tableWidget->setEnabled(true);

}

