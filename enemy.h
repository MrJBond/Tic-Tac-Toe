#ifndef ENEMY_H
#define ENEMY_H

#include "game.h"
#include <utility>

class Enemy : public Game
{
private:

    int checkHor(int index, int num);
    int checkVer(int index, int num);
    pair<int, int> checkDiago(int num);

    vector<vector<int>>* table_ptr;

    // Setter method to set the table pointer
    void setTable(vector<vector<int>>& table) {
        table_ptr = &table;
    }

public:
    Enemy();
    pair<int, int> check();

    // Modified constructor
    Enemy(vector<vector<int>>& table) {
        setTable(table);
    }

    ~Enemy(){
        table_ptr = nullptr;
    }

    vector<pair<int, int>> checkWon(int num); // num is 1 or 2

};

#endif // ENEMY_H
