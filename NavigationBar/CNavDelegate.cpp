#include "CNavDelegate.h"
#include "CNavModel.h"
#include <QPainter>
#include <QColor>

CNavDelegate::CNavDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
    , m_pending(false)
{

}

CNavDelegate::~CNavDelegate()
{

}

QSize CNavDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    CNavModel::TreeNode* pTreeNode = (CNavModel::TreeNode*)index.data(Qt::UserRole).value<void*>();
    if(pTreeNode->nLevel == 1)
        return QSize(50, 45);
    else
        return QSize(50, 28);
}

void CNavDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    CNavModel::TreeNode* pTreeNode = (CNavModel::TreeNode*)index.data(Qt::UserRole).value<void*>();
    painter->setRenderHint(QPainter::Antialiasing); //防走样

    //根据绘制时提供的信息进行背景色绘制
    if ( option.state & QStyle::State_Selected )
    {
        painter->fillRect(option.rect, QColor(133, 153, 216));
    }
    else if ( option.state & QStyle::State_MouseOver )
    {
        painter->fillRect(option.rect, QColor(209, 216, 240));
    }
    else
    {
        if ( pTreeNode->nLevel == 1 )
            painter->fillRect(option.rect, QColor(247, 249, 255));
        else
            painter->fillRect(option.rect, QColor(239, 241, 250));
    }

    //添加图片
    if(pTreeNode->listChildren.size() != 0)
    {
        QString qsImagePath;
        if(!pTreeNode->collapse)
        {
            if ( option.state & QStyle::State_Selected )
                qsImagePath = ":/image/unexpand_selected.png";
            else
                qsImagePath = ":/image/unexpand_normal.png";
        }
        else {
            if ( option.state & QStyle::State_Selected )
                qsImagePath = ":/image/expand_selected.png";
            else
                qsImagePath = ":/image/expand_normal.png";
        }

        //设置图片大小
        QPixmap img(qsImagePath);
        QRect targetRect = option.rect;
        targetRect.setWidth(16);
        targetRect.setHeight(16);

        //设置图片坐标
        QPoint c = option.rect.center();
        c.setX(8);
        targetRect.moveCenter(c);

        //将图片放到对应位置
        painter->drawPixmap(targetRect, qsImagePath, img.rect());
    }
    else {
        QString qsPath = GetImagePath(pTreeNode->nIndex);
        if(qsPath.size())
        {
            QPixmap img(qsPath);
            QRect targetRect = option.rect;
            targetRect.setWidth(16);
            targetRect.setHeight(16);

            //设置图片坐标
            QPoint c = option.rect.center();
            c.setX(12);
            targetRect.moveCenter(c);

            //将图片放到对应位置
            painter->drawPixmap(targetRect, qsPath, img.rect());
        }
    }

    //添加文字
    QPen textPen( option.state & QStyle::State_Selected ? QColor(255, 255, 255) : QColor(58, 58, 58));
    painter->setPen(textPen);

    int margin = 25;

    if ( pTreeNode->nLevel == 2 )
        margin = 45;

    QRect rect = option.rect;
    rect.setWidth(rect.width() - margin);
    rect.setX(rect.x() + margin);

    QFont normalFont("Microsoft Yahei", 9);
    painter->setFont(normalFont);
    painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, index.data(Qt::DisplayRole).toString() );

    //在每一行下方划线
    QPen linePen(QColor(214, 216, 224));
    linePen.setWidth(1);
    painter->setPen(linePen);

    if ( pTreeNode->nLevel == 1
        || (pTreeNode->nLevel == 2 ) )
    {
        painter->drawLine(
            QPointF(option.rect.x(), option.rect.y()+option.rect.height()-1),
            QPointF(option.rect.x() + option.rect.width(), option.rect.y()+option.rect.height()-1));
    }
}

QString CNavDelegate::GetImagePath(int nIndex) const
{
    switch (nIndex)
    {
    case 1:
        return QString();
    case 13:
        return QString("");
    case 16:
        return QString("");
    case 17:
        return QString("");
    default:
        return QString();
    }
}
