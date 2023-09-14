/*******************************************
    @ClassName   : FlawShowWidget
    @Description : Description
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-09-04
********************************************/
#ifndef FLAWSHOWWIDGET_H
#define FLAWSHOWWIDGET_H

#include "FlawDefine.h"
#include "Global.h"
#include <Parameter/JsonRecipeParse.h>
#include <QElapsedTimer>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QResizeEvent>
#include <QScrollArea>
#include <QTimer>
#include <QWidget>
#include <Qwt/qwt_plot.h>
#include <Qwt/qwt_plot_canvas.h>
#include <Qwt/qwt_plot_grid.h>
#include <Qwt/qwt_plot_magnifier.h>
#include <Qwt/qwt_plot_marker.h>
#include <Qwt/qwt_plot_panner.h>
#include <Qwt/qwt_plot_renderer.h>
#include <Qwt/qwt_plot_shapeitem.h>
#include <Qwt/qwt_plot_zoomer.h>
#include <Qwt/qwt_scale_draw.h>
#include <Qwt/qwt_scale_widget.h>
#include <Qwt/qwt_symbol.h>
#include <Qwt/qwt_text.h>

//用不上
class RectanglePlot : public QwtPlot {
public:
    RectanglePlot(QWidget* parent = nullptr)
        : QwtPlot(parent)
    {
        // Create and configure the plot
        setAutoReplot(true);
        //        setAxisTitle(QwtPlot::xBottom, "X Axis");
        //        setAxisTitle(QwtPlot::yLeft, "Y Axis");

        //        enableAxis(QwtPlot::yLeft, true);
        //        enableAxis(QwtPlot::xTop, false);
        //        enableAxis(QwtPlot::yRight, false);
        //        enableAxis(QwtPlot::xBottom, true);

        setAxisScale(QwtPlot::xBottom, 0, 300);
        setAxisScale(QwtPlot::yLeft, 0, 200);

        // Add grid
        //        QwtPlotGrid* grid = new QwtPlotGrid;
        //        grid->attach(this);

        // Create a canvas for the plot
        QwtPlotCanvas* canvas = new QwtPlotCanvas();
        canvas->setBorderRadius(10);
        setCanvas(canvas);
        /*
        // Create markers for the rectangle
        QwtPlotMarker* topLeftMarker = new QwtPlotMarker();
        QwtPlotMarker* bottomRightMarker = new QwtPlotMarker();


        // Configure the markers (change their style, color, etc.)
        topLeftMarker->setSymbol(new QwtSymbol(QwtSymbol::Star2, Qt::NoBrush, QPen(Qt::blue), QSize(10, 10)));
        bottomRightMarker->setSymbol(new QwtSymbol(QwtSymbol::Star2, Qt::NoBrush, QPen(Qt::red), QSize(10, 10)));

        // Attach markers to the plot
        topLeftMarker->attach(this);
        bottomRightMarker->attach(this);

        // Set the marker positions (in plot coordinates)
        topLeftMarker->setValue(QPointF(500, 300));
        bottomRightMarker->setValue(QPointF(4500, 2750));
        */
    }
};

class FlawShowWidget : public QWidget {
    Q_OBJECT
public:
    explicit FlawShowWidget(QWidget* parent = nullptr, JsonRecipeParse* recipe = nullptr);

    enum FlawMoveWay {
        LeftToRightUp = 0,
        RightToLeftUp = 1,
        LeftToRightDown = 2,
        RightToLeftDown = 3
    };

private:
    int w = 300, h = 200;
    int x = 10, y = 10;
    QPainter* m_painter;

    bool isGetGlassSize = false;
    bool isGetFlawPoints = false;
    JsonRecipeParse* m_recipe;

public:
    void drawGlass(double x_length, double y_length); //绘制玻璃
    void drawFlaw(QList<FlawPoint>* m_FlawPointList); //绘制缺陷点

    QList<FlawPoint> FlawPointList;

    QwtPlot* m_plot;

protected:
    void paintEvent(QPaintEvent* e);
    void mouseDoubleClickEvent(QMouseEvent* e);
    void resizeEvent(QResizeEvent* e);

signals:
public slots:
    void slot_resize();
    void slot_GetGlassSize(GLASSINFO* info);
    void slot_GetFlawPoints(QList<FlawPoint>* n_FlawPointList);
    void slot_ChangeFlawShow();
};

#endif // FLAWSHOWWIDGET_H
