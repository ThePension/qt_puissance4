#include "tile.h"

Tile::Tile()
{
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);
    this->x = 0;
    this->y = 0;
    this->tileSize = 10;
    this->color = Colors::EMTPY;
    this->pressed = false;
    this->hovered = false;
}

Tile::Tile(int x, int y, int tileSize)
{
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);
    this->x = x;
    this->y = y;
    this->tileSize = tileSize;
    this->color = Colors::EMTPY;
    this->pressed = false;
    this->hovered = false;
}

void Tile::setColor(Colors color)
{
    this->color = color;
}

void Tile::setIsWinningTile(bool isWinning)
{
    this->isWinningTile = isWinning;
    this->update();
}

void Tile::setIsHovered(Colors color, bool isHovered)
{
    this->hoveredColor = color;
    this->hovered = isHovered;
}

QRectF Tile::boundingRect() const
{
    return QRectF(this->x * this->tileSize, this->y * this->tileSize, this->tileSize, this->tileSize);
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->pressed = true;
    emit this->sigPressEvent(this->x, this->y);
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Tile::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit sigHoveredEvent(this->x);
    update();
    QGraphicsItem::hoverEnterEvent(event);
}

void Tile::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    update();
    QGraphicsItem::hoverLeaveEvent(event);
}

void Tile::paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);

    if(isWinningTile){
        painter->setBrush(Qt::cyan);
        painter->setPen(Qt::cyan);
    }else{
        painter->setBrush(Qt::blue);
        painter->setPen(Qt::blue);
    }

    painter->drawRect(this->x * this->tileSize, this->y * this->tileSize, this->tileSize, this->tileSize);

    if(this->color == Colors::RED){
        painter->setBrush(Qt::red);
    }
    else if(this->color == Colors::YELLOW) {
        painter->setBrush(Qt::yellow);
    }
    else {
        if(this->hovered) {
            if(this->hoveredColor == Colors::RED)
                painter->setBrush(Qt::darkRed);
            else if(this->hoveredColor == Colors::YELLOW)
                painter->setBrush(Qt::darkYellow);
        }
        else painter->setBrush(Qt::white);
    }

    int delta = this->tileSize / 10;
    int ellipseSize = this->tileSize - delta;

    painter->drawEllipse(this->x * this->tileSize + delta / 2, this->y * this->tileSize + delta / 2, ellipseSize, ellipseSize);
}
