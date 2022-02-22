#ifndef TILE_H
#define TILE_H
#include "Colors.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
class Tile : public QGraphicsObject
{
    Q_OBJECT
public:
    Tile();
    Tile(int x, int y, int tileSize);
    void setColor(Colors color);
    Colors getColor() { return this->color; }
    int getX() { return this->x; }
    int getY() { return this->y; }
    bool getIsWinningTile() { return this->isWinningTile; }
    void setIsWinningTile(bool isWinning = true);
    void setIsHovered(Colors color, bool isHovered = true);

    // Events override
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent*event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;

private:
    int x, y, tileSize;
    Colors color, hoveredColor;
    bool pressed;
    bool hovered;
    bool isWinningTile = false;

signals:
    void sigPressEvent(int i, int j);
    void sigHoveredEvent(int j);
};

#endif // TILE_H
