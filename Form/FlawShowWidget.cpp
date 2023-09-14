#include "FlawShowWidget.h"
#include "common_func.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QtDebug>

FlawShowWidget::FlawShowWidget(QWidget* parent, JsonParse* recipe)
    : QWidget(parent)
{
    RECIPE = recipe;
    m_plot = new QwtPlot(this);

    slot_ChangeFlawShow();

    QHBoxLayout* layout0 = new QHBoxLayout(this);
    this->setLayout(layout0);
    layout0->addWidget(m_plot);
}

void FlawShowWidget::drawGlass(double x_length, double y_length)
{
    QwtPlotShapeItem* rectangleItem = new QwtPlotShapeItem;
    rectangleItem->setPen(QPen(Qt::black));
    rectangleItem->setBrush(QBrush(Qt::lightGray));
    QRectF rectangleRect(0, 0, x_length, y_length);

    rectangleItem->setRect(rectangleRect);
    rectangleItem->attach(m_plot);

    isGetGlassSize = false;
}

/*!
    @Function    : drawFlaw
    @Description : 根据缺陷点绘制缺陷，使用qwt_symbol
    @Author      : Chengwenjie
    @Date        : 2023-08-24
*/
void FlawShowWidget::drawFlaw(QList<FlawPoint>* m_FlawPointList)
{

    int ListLength = m_FlawPointList->count();

    for (int i = 0; i < ListLength; i++) {
        QwtPlotMarker* maker = new QwtPlotMarker();

        switch (m_FlawPointList->at(i).FlawType) {
        case 1:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Cross, QBrush(Qt::blue), QPen(Qt::blue), QSize(10, 10)));
            break;
        case 2:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Rect, QBrush(Qt::red), QPen(Qt::red), QSize(10, 10)));
            break;
        case 3:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Star1, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(10, 10)));
            break;
        case 4:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Triangle, QBrush(Qt::blue), QPen(Qt::blue), QSize(10, 10)));
            break;
        case 5:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Diamond, QBrush(Qt::red), QPen(Qt::red), QSize(10, 10)));
            break;
        case 6:
            maker->setSymbol(new QwtSymbol(QwtSymbol::XCross, QBrush(Qt::green), QPen(Qt::darkGreen), QSize(10, 10)));
            break;
        case 7:
            maker->setSymbol(new QwtSymbol(QwtSymbol::Star2, QBrush(Qt::blue), QPen(Qt::blue), QSize(10, 10)));
            break;
        }
        maker->attach(m_plot);
        maker->setValue(QPointF(m_FlawPointList->at(i).x, m_FlawPointList->at(i).y));
    }
    isGetFlawPoints = false;
}

/*!
    @Function    : paintEvent
    @Description : 主要是两点，1:画出尺寸示意图，2：标记缺陷点位置
    @Author      : Chengwenjie
    @Date        : 2023-08-21
*/
void FlawShowWidget::paintEvent(QPaintEvent* e)
{
    //清空上次的点位坐标，加入点位坐标
    //    FlawPointList.clear();

    //    for (int i = 0; i < 7; i++) {
    //        FlawPoint point;
    //        point.x = x + i * 60;
    //        point.y = y + i * 100;
    //        point.FlawType = i + 1;
    //        FlawPointList.append(point);
    //    }
    if (isGetGlassSize && isGetFlawPoints) {

        m_plot->detachItems();
        drawGlass(w, h);
        drawFlaw(&FlawPointList);

        m_plot->replot();
    }
}

/*!
    @Function    : mouseDoubleClickEvent
    @Description : 双击图上标记点可以弹出缺陷小图的信息
    @Author      : Chengwenjie
    @Date        : 2023-08-23
*/
void FlawShowWidget::mouseDoubleClickEvent(QMouseEvent* e)
{
    unsigned int x_screen = e->x();
    unsigned int y_screen = e->y();
    qDebug() << "x:" << x_screen << " y:" << y_screen;

    //屏幕位置与实际位置差的太多
    //如何计算得到真正缺陷位置

    //    //测试
    //    w += 20;
    //    h += 20;
    //    x += 10;
    //    if (h > 600)
    //        h = 600;
    //    if (w > 900)
    //        w = 900;
    //    update();
}

void FlawShowWidget::resizeEvent(QResizeEvent* e)
{
    update();
}

void FlawShowWidget::slot_resize()
{
    update();
}

void FlawShowWidget::slot_GetGlassSize(GLASSINFO* info)
{
    //此处添加实际坐标与显示坐标的转换
    w = info->GlassLength;
    h = info->GlassWidth;
    isGetGlassSize = true;
}

void FlawShowWidget::slot_GetFlawPoints(QList<FlawPoint>* n_FlawPointList)
{
    FlawPointList = *n_FlawPointList;
    isGetFlawPoints = true;
}

void FlawShowWidget::slot_ChangeFlawShow()
{
    QString Keyword4Length = QString::fromLocal8Bit("尺寸测量") + "." + QString::fromLocal8Bit("长度");
    QString Keyword4Width = QString::fromLocal8Bit("尺寸测量") + "." + QString::fromLocal8Bit("长度");
    double length;
    RECIPE->getParameter(Keyword4Length, length);
    double width;
    RECIPE->getParameter(Keyword4Width, width);

    int MaxLength = length > 2000 ? (length + 100) : 2100;
    int MaxWidth = width > 1500 ? (width + 100) : 1600;

    m_plot->setAxisScale(QwtPlot::xBottom, 0, MaxLength);
    m_plot->setAxisScale(QwtPlot::yLeft, 0, MaxWidth);
}
