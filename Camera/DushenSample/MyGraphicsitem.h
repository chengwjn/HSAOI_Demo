#ifndef MYGRAPHICSITEM_H
#define MYGRAPHICSITEM_H

#include <QDragEnterEvent>
#include <QGraphicsItem>
#include <QGraphicsSceneWheelEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QPointF>
#include <QRectF>
#include <QWidget>
#include <QtGui>

class MyGraphicsItem : public QGraphicsItem {
    //Q_OBJECT
public:
    MyGraphicsItem();
    //void    loadPixmap(QPixmap *pixmap);
    void loadImage(QImage pixmap);
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void wheelEvent(QGraphicsSceneWheelEvent* event);
    void ResetItemPos();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    qreal getScaleValue() const;
    void setQGraphicsViewWH(int nwidth, int nheight);

private:
    qreal m_scaleValue;
    qreal m_scaleDafault;
    //QPixmap     m_pix;
    QImage m_pix;
    int m_zoomState;
    bool m_isMove;
    QPointF m_startPos;

    bool m_bFlag = false;
};

#endif // MYGRAPHICSITEM_H
