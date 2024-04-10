/*
 * Author: Jwalant Patel
 * Date: 2024-02-02
 * Description: Tiles class header representing indivdual tiles in the Minesweeper game, with methods
 *              and private variables to manage their values, including whether they are revealed, contain a bomb,
 *              flagged, and the adjacent number of mines
 *
 */

#ifndef TILES_H
#define TILES_H

class Tiles {
public:
    Tiles(int, int);
    ~Tiles();
    bool isRevealed();
    bool isFlagged();
    int getBomb();
    int getRow();
    int getCol();
    void setRevealed(bool);
    void setFlagged(bool);
    void setBomb(int);
    void setRow(int);
    void setCol(int);
    void setAdjacentMines(int);
    int getAdjacentMines();

private:
    int bomb, row, col, minecount;
    bool revealed, flagged;
};

#endif
