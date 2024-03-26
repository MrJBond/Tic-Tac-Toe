#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "board.h"
#include "enemy.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Board b;
    vector<vector<int>> table;
    Enemy e;

    vector<pair<int, int>> checkIfWon();
    bool userWon = false;
    bool enemyWon = false;

public slots:
    void onCellClicked(int a, int b);


private slots:
    void on_buttonReset_clicked();
};
#endif // MAINWINDOW_H
