#include "CNavModel.h"
#include <QFile>
#include <QDomDocument>
#include <QDebug>

CNavModel::CNavModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

CNavModel::~CNavModel()
{

    QVector<TreeNode*>  m_vecTreeNode;      //用于存储对应关系
    QVector<ListNode>   m_vecListNode;      //存储所有的节点
    for(QVector<TreeNode*>::iterator it = m_vecTreeNode.begin(); it != m_vecTreeNode.end(); it++)
    {
        if((*it)->listChildren.size())
        {
            for (QList<TreeNode*>::iterator itChild = (*it)->listChildren.begin(); itChild != (*it)->listChildren.end(); it++)
                delete (*itChild);
        }
        delete (*it);
    }

    m_vecListNode.clear();
    m_vecTreeNode.clear();
}

int CNavModel::rowCount(const QModelIndex &parent) const
{
    return m_vecListNode.size();
}

QVariant CNavModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
        return QVariant();

    if ( index.row() >= m_vecListNode.size() || index.row() < 0 )
        return QVariant();

    if ( role == Qt::DisplayRole )      //显示文字
        return m_vecListNode[index.row()].qsLabelName;
    else if ( role == Qt::UserRole )    //用户定义起始位置
        return QVariant::fromValue((void*)m_vecListNode[index.row()].pTreeNode);

    return QVariant();
}

void CNavModel::ReadConfig(QString qsPath)
{
    QFile xmlFile(qsPath);
    if(!xmlFile.open(QFile::ReadOnly | QFile::Text))
        return;

    QDomDocument docXml;
    QString error;
    if(!docXml.setContent(&xmlFile, false, &error))
    {
        xmlFile.close();
        return;
    }

    QDomElement xmlRoot = docXml.documentElement(); //返回根节点
    QDomNode domNode = xmlRoot.firstChild(); //获取子节点，一级节点
    while (!domNode.isNull())
    {
        if(domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();   //一级节点
            TreeNode* pTreeNode = new TreeNode;

            pTreeNode->qsLableName = domElement.attribute("lable");//获取一级节点的lable
            pTreeNode->nLevel = 1;  //标志一级节点
            pTreeNode->collapse =  domElement.attribute("collapse").toInt(); //标志是否展开
            pTreeNode->nIndex = domElement.attribute("index").toInt();  //获取标志

            QDomNodeList list = domElement.childNodes();    //获取二级节点
            for(int i = 0; i < list.count(); i++)
            {
                QDomElement secNodeInfo = list.at(i).toElement();
                TreeNode* pSecNode = new TreeNode;
                pSecNode->qsLableName = secNodeInfo.attribute("lable");
                pSecNode->nLevel = 2;
                pSecNode->nIndex = secNodeInfo.attribute("index").toInt();
                pTreeNode->collapse = false;
                pTreeNode->listChildren.push_back(pSecNode);
            }
            m_vecTreeNode.push_back(pTreeNode);
        }
        domNode = domNode.nextSibling();    //下一一级节点
    }

    xmlFile.close();
    RefreshList();  //刷新界面标题栏展示数据
    beginInsertRows(QModelIndex(), 0, m_vecListNode.size());    //插入所有节点
    endInsertRows(); //结束插入
}

void CNavModel::RefreshList()
{
    m_vecListNode.clear();
    for(QVector<TreeNode*>::iterator it = m_vecTreeNode.begin(); it != m_vecTreeNode.end(); it++)
    {
        //一级节点
        ListNode node;
        node.qsLabelName = (*it)->qsLableName;
        node.pTreeNode = *it;
        m_vecListNode.push_back(node);

        if(!(*it)->collapse) //如果一级节点未展开，则插入下一一级节点
            continue;

        for(QList<TreeNode*>::iterator child = (*it)->listChildren.begin(); child != (*it)->listChildren.end(); child++)
        {
            ListNode node;
            node.qsLabelName = (*child)->qsLableName;
            node.pTreeNode = *child;
            m_vecListNode.push_back(node);
        }
    }
}

void CNavModel::Collapse(const QModelIndex& index)
{
    TreeNode* pTreeNode = m_vecListNode[index.row()].pTreeNode; //获取当前点击节点
    if(pTreeNode->listChildren.size() == 0) //如果该节点没有子节点 则返回
        return;

    pTreeNode->collapse = !pTreeNode->collapse; //刷新是否展开标志

    if(!pTreeNode->collapse)    //如果是不展开，即为展开变成合并，移除合并的
    {
        beginRemoveRows(QModelIndex(), index.row() + 1, pTreeNode->listChildren.size()); //默认起始节点为最初节点
        endRemoveRows();
    }
    else {
        beginInsertRows(QModelIndex(), index.row() + 1, pTreeNode->listChildren.size());
        endInsertRows();
    }
    RefreshList(); //更新界面显示节点数据
}

void CNavModel::Refresh()
{
    RefreshList();
    beginResetModel();
    endResetModel();
}

void CNavModel::ExpandAllNodes()
{
    for (int i = 0; i < m_vecListNode.size(); ++i)
    {
        TreeNode* pTreeNode = m_vecListNode[i].pTreeNode;
        if (!pTreeNode->collapse)
        {
            pTreeNode->collapse = true;

            // 插入子项，用于展开节点
            beginInsertRows(QModelIndex(), i + 1, i + 1 + pTreeNode->listChildren.size());
            endInsertRows();
        }
    }

    RefreshList(); // 更新界面显示节点数据
}
