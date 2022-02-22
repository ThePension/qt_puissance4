#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "tile.h"
#include "config.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // Methods
    void setupNewGame();
    Colors checkWinner();
    void resetGame();
    void clearGrid();

    // Attributes
    Colors currentColor;
    QGraphicsScene * gameScene;
    QGraphicsView  * mainview;
    Tile * grid[config::width/config::tileSize][config::height/config::tileSize];
    Tile * lastHoveredTile = nullptr;
    bool isGameOver = false;

protected:
    void keyPressEvent(QKeyEvent *) override;

public slots:
    void drawGrid();
    void tilePressed(int i, int j);
    void tileHovered(int j);
};
#endif // WIDGET_H
