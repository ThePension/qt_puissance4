#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    currentColor = Colors::RED;

    mainview = new QGraphicsView(this);
    mainview->setSceneRect(0, 0, config::width, config::height);

    gameScene = new QGraphicsScene(this);

    mainview->setScene(gameScene);
    this->setupNewGame();
    this->drawGrid();
    mainview->show();
}

Widget::~Widget()
{

}

void Widget::setupNewGame()
{
    for(int i = 0; i < config::width/config::tileSize; i++){
        for(int j = 0; j < config::height/config::tileSize; j++){
            grid[i][j] = new Tile(i, j, config::tileSize);
            connect(grid[i][j], &Tile::sigPressEvent, this, &Widget::tilePressed);
            connect(grid[i][j], &Tile::sigHoveredEvent, this, &Widget::tileHovered);
        }
    }
}

void Widget::clearGrid() {
    for(int i = 0; i < config::width/config::tileSize; i++){
        for(int j = 0; j < config::height/config::tileSize; j++){
            if(grid[i][j] != nullptr) delete grid[i][j];
        }
    }
}

Colors Widget::checkWinner()
{
    int cols = config::width / config::tileSize;
    int rows = config::height / config::tileSize;

    // CHECK VERTICAL LINES
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows - 3; j++){
            Tile * tile1 = grid[i][j + 0];
            Tile * tile2 = grid[i][j + 1];
            Tile * tile3 = grid[i][j + 2];
            Tile * tile4 = grid[i][j + 3];

            if( tile1->getColor() != Colors::EMTPY &&
                tile1->getColor() == tile2->getColor() &&
                tile2->getColor() == tile3->getColor() &&
                tile3->getColor() == tile4->getColor())
            {
                tile1->setIsWinningTile();
                tile2->setIsWinningTile();
                tile3->setIsWinningTile();
                tile4->setIsWinningTile();
                return tile1->getColor();
            }
        }
    }

    // CHECK HORIZONTAL LINES
    for(int i = 0; i < cols - 3; i++){
        for(int j = 0; j < rows; j++){
            Tile * tile1 = grid[i + 0][j];
            Tile * tile2 = grid[i + 1][j];
            Tile * tile3 = grid[i + 2][j];
            Tile * tile4 = grid[i + 3][j];

            if( tile1->getColor() != Colors::EMTPY &&
                tile1->getColor() == tile2->getColor() &&
                tile2->getColor() == tile3->getColor() &&
                tile3->getColor() == tile4->getColor())
            {
                tile1->setIsWinningTile();
                tile2->setIsWinningTile();
                tile3->setIsWinningTile();
                tile4->setIsWinningTile();
                return tile1->getColor();
            }
        }
    }

    // CHECK DIAGONAL LINES (START TO END)
    for(int i = 0; i < cols - 3; i++){
        for(int j = 0; j < rows - 3; j++){
            Tile * tile1 = grid[i + 0][j + 0];
            Tile * tile2 = grid[i + 1][j + 1];
            Tile * tile3 = grid[i + 2][j + 2];
            Tile * tile4 = grid[i + 3][j + 3];

            if( tile1->getColor() != Colors::EMTPY &&
                tile1->getColor() == tile2->getColor() &&
                tile2->getColor() == tile3->getColor() &&
                tile3->getColor() == tile4->getColor())
            {
                tile1->setIsWinningTile();
                tile2->setIsWinningTile();
                tile3->setIsWinningTile();
                tile4->setIsWinningTile();
                return tile1->getColor();
            }
        }
    }

    // CHECK DIAGONAL LINES (END TO START)
    for(int i = 0; i < cols - 3; i++){
        for(int j = rows - 1; j >= 3; j--){
            Tile * tile1 = grid[i + 0][j - 0];
            Tile * tile2 = grid[i + 1][j - 1];
            Tile * tile3 = grid[i + 2][j - 2];
            Tile * tile4 = grid[i + 3][j - 3];

            if( tile1->getColor() != Colors::EMTPY &&
                tile1->getColor() == tile2->getColor() &&
                tile2->getColor() == tile3->getColor() &&
                tile3->getColor() == tile4->getColor())
            {
                tile1->setIsWinningTile();
                tile2->setIsWinningTile();
                tile3->setIsWinningTile();
                tile4->setIsWinningTile();
                return tile1->getColor();
            }
        }
    }

    return Colors::EMTPY; // NO WIN
}

void Widget::resetGame()
{
    isGameOver = false;
    currentColor = Colors::RED;
    gameScene->clear();
    lastHoveredTile = nullptr;
    setupNewGame();
    drawGrid();
}

void Widget::keyPressEvent(QKeyEvent * qe)
{
    if(qe->key() == Qt::Key::Key_R){
        resetGame();
    }
}

void Widget::drawGrid()
{
    for(int i = 0; i < config::width/config::tileSize; i++){
        for(int j = 0; j < config::height/config::tileSize; j++){
            gameScene->addItem(grid[i][j]);
        }
    }
}

void Widget::tilePressed(int i, int j)
{
    Q_UNUSED(j);

    Tile * pressedTile = lastHoveredTile;
    if(pressedTile != nullptr){
        if(pressedTile->getColor() == Colors::EMTPY) {
            pressedTile->setColor(currentColor);
            pressedTile->update();

            if(currentColor == Colors::RED) currentColor = Colors::YELLOW;
            else currentColor = Colors::RED;

            lastHoveredTile = nullptr;
            tileHovered(i);

            if(checkWinner() != Colors::EMTPY) isGameOver = true;
        }
    }
}

void Widget::tileHovered(int i)
{
    if(lastHoveredTile != nullptr) {
        lastHoveredTile->setIsHovered(currentColor, false);
        lastHoveredTile->setColor(Colors::EMTPY);
        lastHoveredTile->update();
    }

    int rows = (config::height / config::tileSize) - 1;

    Tile * firstEmptyTile = grid[i][rows];

    while(firstEmptyTile->getColor() != Colors::EMTPY && rows >= 0){
        firstEmptyTile = grid[i][--rows];
    }

    if(rows == -1) lastHoveredTile = nullptr;
    else{
        firstEmptyTile->setIsHovered(currentColor);
        firstEmptyTile->update();
        lastHoveredTile = firstEmptyTile;
    }
}
