#ifndef CNAVMODEL_H
#define CNAVMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVector>

class CNavModel : public QAbstractListModel
{
    Q_OBJECT
public:
    struct TreeNode
    {
        QString qsLableName;
        int nLevel;
        bool collapse;
        int nIndex;
        QList<TreeNode* > listChildren;
    };

    struct ListNode
    {
        QString qsLabelName;
        TreeNode* pTreeNode;
    };

public:
    explicit CNavModel(QObject *parent = nullptr);
    ~CNavModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public:
    void ReadConfig(QString qsPath);    //读取导航栏节点陪值文件
    void Refresh(); //刷新模型
    void ExpandAllNodes();

public slots:
    void Collapse(const QModelIndex& index);    //节点展开、收缩槽函数

private:
    void RefreshList();     //刷新当前界面显示的节点

private:
    QVector<TreeNode*>  m_vecTreeNode;      //用于存储对应关系
    QVector<ListNode>   m_vecListNode;      //存储所有的节点
};

#endif // CNAVMODEL_H
