#ifndef GAME_H
#define GAME_H

#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Game
{
protected:

    static const int size = 3;

public:

    int getSize() const {
        return size;
    }
    Game(){

    };

};

#endif // GAME_H
