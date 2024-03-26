#include "enemy.h"

Enemy::Enemy() {

}

int Enemy::checkHor(int index, int num){ // num is 1 or 2
    if((*table_ptr)[index][0] == num
        && (*table_ptr)[index][1] == num
        && (*table_ptr)[index][2] == 0){
        return 2;
    }
    if((*table_ptr)[index][0] == num
        && (*table_ptr)[index][2] == num
        && (*table_ptr)[index][1] == 0){
        return 1;
    }
    if((*table_ptr)[index][1] == num
        && (*table_ptr)[index][2] == num
        && (*table_ptr)[index][0] == 0){
        return 0;
    }
    return -1;
}

int Enemy::checkVer(int index, int num){
    if((*table_ptr)[0][index] == num
        && (*table_ptr)[1][index] == num
        && (*table_ptr)[2][index] == 0){
        return 2;
    }
    if((*table_ptr)[0][index] == num
        && (*table_ptr)[2][index] == num
        && (*table_ptr)[1][index] == 0){
        return 1;
    }
    if((*table_ptr)[1][index] == num
        && (*table_ptr)[2][index] == num
        && (*table_ptr)[0][index] == 0){
        return 0;
    }
    return -1;
}
pair<int, int> Enemy::checkDiago(int num){

    // main diago
    if((*table_ptr)[0][0] == num
        && (*table_ptr)[2][2] == num
        && (*table_ptr)[1][1] == 0){
        return make_pair(1,1);
    }
    if((*table_ptr)[0][0] == num
        && (*table_ptr)[1][1] == num
        && (*table_ptr)[2][2] == 0){
        return make_pair(2,2);
    }
    if((*table_ptr)[1][1] == num
        && (*table_ptr)[2][2] == num
        && (*table_ptr)[0][0] == 0){
        return make_pair(0,0);
    }

    // second diago
    if((*table_ptr)[0][2] == num
        && (*table_ptr)[1][1] == num
        && (*table_ptr)[2][0] == 0){
        return make_pair(2,0);
    }
    if((*table_ptr)[0][2] == num
        && (*table_ptr)[2][0] == num
        && (*table_ptr)[1][1] == 0){
        return make_pair(1,1);
    }
    if((*table_ptr)[1][1] == num
        && (*table_ptr)[2][0] == num
        && (*table_ptr)[0][2] == 0){
        return make_pair(0,2);
    }
    return make_pair(-1,-1);
}

pair<int, int> Enemy::check(){
    if((*table_ptr)[1][1] == 0){ // center
        return make_pair(1,1);
    }

    // When two cells are taken
    vector<pair<int, int>> variants1;
    vector<pair<int, int>> variants2;

    // check 1
    for(int i = 0; i < size; i++){
        variants1.push_back(make_pair(i, checkHor(i,1)));
        variants1.push_back(make_pair(checkVer(i,1), i));
    }
    variants1.push_back(checkDiago(1));

    // check 2
    for(int i = 0; i < size; i++){
        variants2.push_back(make_pair(i, checkHor(i,2)));
        variants2.push_back(make_pair(checkVer(i,2), i));
    }
    variants2.push_back(checkDiago(2));

    // remove all with -1
    variants1.erase(std::remove_if(variants1.begin(), variants1.end(), [](const auto& p) {
                       return p.first == -1 || p.second == -1;
                   }), variants1.end());

    variants2.erase(std::remove_if(variants2.begin(), variants2.end(), [](const auto& p) {
                        return p.first == -1 || p.second == -1;
                    }), variants2.end());

    // check what we have

    if(!variants2.empty()){
        if((*table_ptr)[variants2[0].first][variants2[0].second] == 0)
            return variants2[0];
    }
    if(!variants1.empty()){
        if((*table_ptr)[variants1[0].first][variants1[0].second] == 0)
            return variants1[0];
    }

    // if 1 or 0 cells are taken

    // return random pos.

    srand(time(NULL));
    int x = rand() % 3;
    int y = rand() % 3;

    // if the cell is taken
    if((*table_ptr)[x][y] != 0){
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                if((*table_ptr)[i][j] == 0){
                    x = i;
                    y = j;
                }
            }
        }
    }
    if((*table_ptr)[x][y] == 0)
        return make_pair(x,y);

    return make_pair(-1,-1); // base case
}

vector<pair<int, int>> Enemy::checkWon(int num){
    vector<pair<int, int>> res(size, make_pair(-1,-1));
    for(int i = 0; i<size; i++){
        // check raws
        if((*table_ptr)[i][0] == num &&
           (*table_ptr)[i][1] == num &&
            (*table_ptr)[i][2] == num){
            res[0] = make_pair(i,0);
            res[1] = make_pair(i,1);
            res[2] = make_pair(i,2);
            return res;
        }
        // check cols
        if((*table_ptr)[0][i] == num &&
            (*table_ptr)[1][i] == num &&
            (*table_ptr)[2][i] == num){
            res[0] = make_pair(0,i);
            res[1] = make_pair(1,i);
            res[2] = make_pair(2,i);
            return res;
        }
    }
    // check diago
    if((*table_ptr)[0][0] == num &&
        (*table_ptr)[1][1] == num &&
        (*table_ptr)[2][2] == num ){
        res[0] = make_pair(0,0);
        res[1] = make_pair(1,1);
        res[2] = make_pair(2,2);
        return res;
    }

    if((*table_ptr)[0][2] == num &&
        (*table_ptr)[1][1] == num &&
        (*table_ptr)[2][0] == num ){
        res[0] = make_pair(0,2);
        res[1] = make_pair(1,1);
        res[2] = make_pair(2,0);
        return res;
    }
    return res;
}
