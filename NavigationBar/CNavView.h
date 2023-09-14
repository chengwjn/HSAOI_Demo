#ifndef CNAVVIEW_H
#define CNAVVIEW_H

#include <QObject>
#include <QListView>

class CNavView : public QListView
{
    Q_OBJECT

public:
    CNavView(QWidget *parent);
    ~CNavView();
};

#endif // CNAVVIEW_H
