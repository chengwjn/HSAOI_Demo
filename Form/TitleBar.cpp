#include "TitleBar.h"
#include "Global.h"
#include <QHBoxLayout>

#define TITLEBAR_HEIGHT 40

TitleBar::TitleBar(QWidget* parent)
    : QWidget(parent)
{
    setFixedHeight(TITLEBAR_HEIGHT);
    int button_size = TITLEBAR_HEIGHT - 5;
    int icon_size = button_size - 10;

    m_pTitleLabel = new QLabel(this);
    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pTitleLabel->setText(Global::SystemName);
    m_pTitleLabel->setStyleSheet("font: 75 24pt \"微软雅黑\"; color: rgb(0, 0, 200);");

    QHBoxLayout* layout1 = new QHBoxLayout(this);
    layout1->addWidget(m_pTitleLabel);
    layout1->setAlignment(m_pTitleLabel, Qt::AlignCenter);
    layout1->setMargin(0);
}
