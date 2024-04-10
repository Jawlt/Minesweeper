/* 
 * Author: Jwalant Patel
 * Date: 2024-02-02
 * Description: MainWindow class for a Minesweeper like game in C++ leveraging the QT framework,
 *              initalizing the, variables, and other identifiers. Contains the game logic with the use of functions
 *              and arrays, Tiles, and buttons.
 *
 */
#include "mainwindow.h"

//constuctor initializes the window of the application
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  //Creates a central widget and gridlayout
  QWidget *centralWidget = new QWidget(this);
  grid = new QGridLayout();
  grid->setSpacing(0);

  //Initializes game variables
  totalMoves = 0;
  gameOver = false;
  createGridButtons();

  //applys grid layout to centralwdiget
  centralWidget->setLayout(grid);
  setCentralWidget(centralWidget);
}

//Destructor 
MainWindow::~MainWindow() {
  //Cleanup code if any
}

/* Creates a 2D array of Tiles and MyPushButton, while setting the size and polixy of the buttons
 *  Creates a connection between the left and right clicks events of the buttons which are added to the grid
 */
void MainWindow::createGridButtons(){
  for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < COLS; j++){
      tilesGrid[i][j] = new Tiles(i, j);
      gridButtons[i][j] = new MyPushButton;
      gridButtons[i][j]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
      gridButtons[i][j]->setFixedSize(30, 30);

      connect(gridButtons[i][j], &QPushButton::clicked, this, [this, i, j](){
        handleLeftClick(i, j);
      });
      connect(gridButtons[i][j], &MyPushButton::customRightClickSignal, this, [this, i, j](){
        handleRightClick(i, j);
      });

      grid->addWidget(gridButtons[i][j], i, j);
    }
  }
}

/* Handles all left click events of the game
 */
void MainWindow::handleLeftClick(int row, int col) {
  QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
  if(clickedButton) {
    handleTileClick(row, col);
  }
}

/* Handles all right click events of the game
 */
void MainWindow::handleRightClick(int row, int col) {
  // Disables right click when game has been lost or won
  if(gameOver == true){
    return;
  }
  //Disables right clicked when a tile is revealed
  if(tilesGrid[row][col]->isRevealed()){
    return;
  }

  /* Places a flag icon on unrevealed tiles, and removes flags if a flag is on the current tile
   * Renables the button if there is a flag placed or removed
   */
  QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
  if(clickedButton) {
    if(tilesGrid[row][col]->isFlagged() == false) {
      tilesGrid[row][col]->setFlagged(true);
      clickedButton->setEnabled(true);
      gridButtons[row][col]->setIcon(QIcon(":/minesweeper_icons/mine_flag.png"));
      gridButtons[row][col]->setIconSize(QSize(26, 26));
    }
    else {
      tilesGrid[row][col]->setFlagged(false);
      gridButtons[row][col]->setIcon(QIcon());
      clickedButton->setEnabled(true);
    }
  }
}

/* tileClick function which handles all of left click events calls
 */
void MainWindow::handleTileClick(int row, int col){
  //Disables left click feature when game is lost or won
  if(gameOver == true){
    return;
  }

  //Places bombs after first move, can never lose on first click
  if(totalMoves == 0) {
    placeBombs(row, col);
    totalAdjacentMines();
  }

  //When a tile is flagged or revealed you can no longer left click
  if(tilesGrid[row][col]->isFlagged() || tilesGrid[row][col]->isRevealed()){
    return;
  }
  
  //if clicked box has mine (lose game and show all mines)
  if(tilesGrid[row][col]->getBomb() == 1){
    revealMinesExploded();
    return;
  }

  //Reveals clicked tile and updates tile
  tilesGrid[row][col]->setRevealed(true);
  updateTile(row, col); // Updates the tiles info e.g. # of adjacent  mines
  
  //If the tile has no adjacent mines, reveal adjacent tiles
  if(tilesGrid[row][col]->getAdjacentMines() == 0){
    revealAdjacentTiles(row, col);
  }
  //increment game moves (doesn't place mine 2nd time around)
  totalMoves++;

  //Check if the player has won
  if(checkWinCon() && totalMoves > 0){
    handleWin();
  }
}

/* Reveal mine exploded function, when player loses reveals all mines with the exploded mine png
 */
void MainWindow::revealMinesExploded(){
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
        gridButtons[i][j]->setEnabled(true);
        //if tile contains a bomb then set the icon
        if (tilesGrid[i][j]->getBomb() == 1) {
            gridButtons[i][j]->setIcon(QIcon(":/minesweeper_icons/bomb_explode.png"));
        } 
        gridButtons[i][j]->setIconSize(QSize(26, 26)); //set image size smaller than the button size
    }
  }
  handleLoss();
}

/* Reveals mine function, when player wins reveals all mines with the mine png
 */
void MainWindow::revealMines(){
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
        gridButtons[i][j]->setEnabled(true);
        //if tile contains a bomb then set the icon
        if (tilesGrid[i][j]->getBomb() == 1) {
            gridButtons[i][j]->setIcon(QIcon(":/minesweeper_icons/bomb.png"));
        }
        gridButtons[i][j]->setIconSize(QSize(26, 26)); //set image size smaller than the button size
    }
  }
}

/* Places bomb function, after the first tile is clicked randomly place mines accorss the grid
*/
void MainWindow::placeBombs(int r, int c) {
  //loop until all mines are placed
  for(int i = 0; i < MAXMINES;) {
    //generates number bounded by max rows and column
    int row = QRandomGenerator::global()->bounded(ROWS);
    int col = QRandomGenerator::global()->bounded(COLS);

    //if bomb is generated at r and c then regen mine at a different spot  
    if(row == r && col == c){
      continue;
    }

    if(tilesGrid[row][col]->getBomb() == 0){
      tilesGrid[row][col]->setBomb(1);  //update bomb in tile so 1 means bomb is present 
      i++;
    }
  }
}

/* Caclulates total mines around clicked tile
*/
void MainWindow::totalAdjacentMines(){
  for (int row = 0; row < ROWS; ++row) {
    for (int col = 0; col < COLS; ++col) {
      if (tilesGrid[row][col]->getBomb() == 1) {
        continue; //skip if a bomb
      }

      int mineCount = 0; //total mines around tile
      //loops around the 8 adjacent tiles
      for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
          int newRow = row + i;
          int newCol = col + j;

          //checks if adjacent tile is within bounds and is a bomb
          if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && tilesGrid[newRow][newCol]->getBomb() == 1) {
            mineCount++;
          }
        }
      }
      //set the mine count to the tile
      tilesGrid[row][col]->setAdjacentMines(mineCount);
    }
  }
}

/* Recursively reveals adjacent tiles, updating their icons based on whether
 * they are flagged, mine or are adjacent to mines 
 */
void MainWindow::revealAdjacentTiles(int row, int col){
  gridButtons[row][col]->setIcon(QIcon(":/minesweeper_icons/0.png"));
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int newRow = row + i;
      int newCol = col + j;

      //check bounds
      if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
        //only reveal if not already revealed and (flagged and not a mine)
        if(!tilesGrid[newRow][newCol]->isRevealed() && (tilesGrid[newRow][newCol]->isFlagged() && tilesGrid[newRow][newCol]->getBomb() == 0)){
          tilesGrid[newRow][newCol]->setFlagged(false);
        }

        //if not revealed update tile
        if(!tilesGrid[newRow][newCol]->isRevealed()){
          tilesGrid[newRow][newCol]->setRevealed(true);
          updateTile(newRow, newCol);
          //if 0 adjacent mines then recall function
          if(tilesGrid[newRow][newCol]->getAdjacentMines() == 0) {
            revealAdjacentTiles(newRow, newCol);
          }
        }
      }
    }
  }
}

/* update tile function that sets icon, icon size, to the amount of adjacent mines
 */
void MainWindow::updateTile(int row, int col){
  if(tilesGrid[row][col]->isRevealed()){
    int adjacentMines = tilesGrid[row][col]->getAdjacentMines();
    gridButtons[row][col]->setIcon(adjacentMines > 0 ? QIcon(getNumberImage(adjacentMines)) : QIcon(":/minesweeper_icons/0.png"));
    gridButtons[row][col]->setIconSize(QSize(26, 26));
    gridButtons[row][col]->setEnabled(true);
  }
}

/* Get number image function that returns correct icon based on the adjacent mines
 */
QIcon MainWindow::getNumberImage(int num){
  switch(num){
    case 1:
      return QIcon(":/minesweeper_icons/1.png");
    case 2:
      return QIcon(":/minesweeper_icons/2.png");
    case 3:
      return QIcon(":/minesweeper_icons/3.png");
    case 4:
      return QIcon(":/minesweeper_icons/4.png");
    case 5:
      return QIcon(":/minesweeper_icons/5.png");
    case 6:
      return QIcon(":/minesweeper_icons/6.png");
    case 7:
      return QIcon(":/minesweeper_icons/7.png");
    case 8:
      return QIcon(":/minesweeper_icons/8.png");
    default:
      //never reaches here
      return QIcon();
  }
}

/* win condiction function checks all tiles
*/
bool MainWindow::checkWinCon(){
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      //if a no mine tile is not revealed, the player hasn't won yet
      if (tilesGrid[i][j]->getBomb() == 0 && !tilesGrid[i][j]->isRevealed()) {
        return false;
      }
    }
  }
  return true; //all no mine tiles are revealed, player wins
}


/* handle win function disables and game interactions and prompts the play that they have won
 * and provides them with two options "play again!" and "exit" and proceed based on the choice
 */
void MainWindow::handleWin(){
  revealMines();
  gameOver = true;

  //display a game won message
  QMessageBox gameWonPrompt;
  gameWonPrompt.setWindowTitle("Game Over");
  gameWonPrompt.setText("You Win!");
  gameWonPrompt.setInformativeText("Do you want to Play Again?");
  gameWonPrompt.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
  gameWonPrompt.setDefaultButton(QMessageBox::Retry);

  //change button text
  gameWonPrompt.button(QMessageBox::Retry)->setText("Play Again!");
  gameWonPrompt.button(QMessageBox::Cancel)->setText("Exit");

  int returnValue = gameWonPrompt.exec();

  switch(returnValue){
    case QMessageBox::Retry:
      //restarts game
      resetGame();
      break;
    case QMessageBox::Cancel:
      //closes application
      close();
    default:
      //never reaches here 
      break;
  }
}

/* handle lose function disables and game interactions and prompts the play that they have lost
 * and provides them with two options "retry" and "exit" and proceed based on the choice
 */
void MainWindow::handleLoss(){
  gameOver = true;

  //displays game lost message
  QMessageBox gameLostPrompt;
  gameLostPrompt.setWindowTitle("Game Over");
  gameLostPrompt.setText("You clicked on a mine and exploded!");
  gameLostPrompt.setInformativeText("Do you want to retry?");
  gameLostPrompt.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
  gameLostPrompt.setDefaultButton(QMessageBox::Retry);

  //change button text
  gameLostPrompt.button(QMessageBox::Retry)->setText("Retry!");
  gameLostPrompt.button(QMessageBox::Cancel)->setText("Exit");

  int returnValue = gameLostPrompt.exec();

  switch(returnValue){
    case QMessageBox::Retry:
      //restarts game
      resetGame();
      break;
    case QMessageBox::Cancel:
      //closes application
      close();
    default:
      //never reaches here
      break;
  }
}

/* reset game function that loops through all of the 2D array
 * sets all variables, tileGrid and gridButtons to original state
 */
void MainWindow::resetGame(){
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      gridButtons[i][j]->setEnabled(true);
      gridButtons[i][j]->setIcon(QIcon());
      gridButtons[i][j]->setText("");
      gridButtons[i][j]->setVisible(true);

      tilesGrid[i][j] = new Tiles(i,j);

      gameOver = false;
      totalMoves = 0;
    }
  }
}
