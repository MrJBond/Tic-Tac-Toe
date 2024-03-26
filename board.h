#ifndef BOARD_H
#define BOARD_H

#include "game.h"
#include "qheaderview.h"
#include <QTableWidget>


class Board : public Game
{

public:

    Board();

    Board(QTableWidget& w){

        w.setColumnCount(size);
        w.setRowCount(size);

        // make them squares
        for(int i = 0; i<size; i++){
           w.setRowHeight(i, 200);
           w.setColumnWidth(i,200);
        }
        w.horizontalHeader()->hide();
        w.verticalHeader()->hide();

        // Set the edit triggers to NoEditTriggers
        w.setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

};

#endif // BOARD_H
