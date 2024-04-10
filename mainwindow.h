/*
 * Author: Jwalant Patel
 * Date: 2024-02-02
 * Description: MainWindow header for a Minesweeper like game in C++ leveraging the QT framework,
 *              containing the functions, classes, variables, and other identifiers.
 * 
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QIcon>
#include <QMessageBox>
#include <QDebug>
#include <QRandomGenerator>
#include "tiles.h"
#include "mypushbutton.h"

//contants used to set up the game (e.g. a 16x30 game size with a max of 99 mines)
#define MAXMINES 99
#define ROWS 16
#define COLS 30

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots: 
  void createGridButtons();
  void placeBombs(int, int); //place mines function (only runs after 1st move)
  void handleLeftClick(int row, int col);
  void handleRightClick(int row, int col);
  void revealMinesExploded();
  void revealMines();
  void handleTileClick(int, int);
  void totalAdjacentMines();
  void revealAdjacentTiles(int, int);
  void updateTile(int, int);
  bool checkWinCon();
  void handleWin();
  void handleLoss();
  void resetGame();
  QIcon getNumberImage(int);


private:
  int totalMoves; //moves done by player
  bool gameOver;
  QGridLayout *grid;
  MyPushButton *gridButtons[ROWS][COLS];
  Tiles *tilesGrid[ROWS][COLS];
};

#endif // MAINWINDOW_H
