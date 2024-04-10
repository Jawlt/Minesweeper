/*
 * Author: Jwalant Patel
 * Date: 2024-02-02
 * Description: Tiles class representing indivdual tiles in the Minesweeper game, with methods
 *              and private variables to manage their values, including whether they are revealed, contain a bomb,
 *              flagged, and the adjacent number of mines
 *
 */

#include "tiles.h"

/* 
 * constuctor for tile class 
 * that sets the default values for all variables
 */
Tiles::Tiles(int r, int c){
    row = r;
    col = c;
    bomb = 0;
    revealed = false;
    flagged = false;
    minecount = 0;
}

//deconstructor
Tiles::~Tiles(){

}

/* 
 * get method for revealed variable
 */
bool Tiles::isRevealed(){
    return revealed;
}

/* 
 * get method for flagged variable
 */
bool Tiles::isFlagged(){
    return flagged;
}

/* 
 * get method for bomb variable
 */
int Tiles::getBomb(){
    return bomb;
}

/* 
 * set method for revealed variable
 */
void Tiles::setRevealed(bool revealed){
    this->revealed = revealed;
}

/* 
 * set method for flagged variable
 */
void Tiles::setFlagged(bool flagged){
    this->flagged = flagged;
}

/* 
 * set method for bomb variable
 */
void Tiles::setBomb(int bomb){
    this->bomb = bomb;
}

/* 
 * set method for row variable
 */
void Tiles::setRow(int row){
    this->row = row;
}

/* 
 * set method for col variable
 */
void Tiles::setCol(int col){
    this->col = col;
}

/* 
 * get method for row variable
 */
int Tiles::getRow(){
    return row;
}

/* 
 * get method for col variable
 */
int Tiles::getCol(){
    return col;
}

/* 
 * get method for minecount variable
*/
int Tiles::getAdjacentMines() {
    return minecount;
}

/* 
 * set method for minecount variable
 */
void Tiles::setAdjacentMines(int minecount) {
    this->minecount = minecount;
}
