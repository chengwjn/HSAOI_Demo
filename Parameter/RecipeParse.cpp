#include "RecipeParse.h"

RecipeParse::RecipeParse(QObject* parent, QString RecipeName)
    : QObject(parent)
{
    m_RecipeName = RecipeName;
    QString Recipe_Addr = "Recipes/" + m_RecipeName + ".xml";
    qDebug() << Recipe_Addr;
    RecipeXml = new XmlParse(Recipe_Addr);
    InitParams();
}

void RecipeParse::InitParams()
{
    ReadParams();
}

void RecipeParse::ReadParams()
{
    RecipeXml->getParameter("Length", Read_Length);
    RecipeXml->getParameter("Width", Read_Width);
    RecipeXml->getParameter("Diagonal1", Read_Diagonal1);
    RecipeXml->getParameter("Diagonal2", Read_Diagonal2);

    RecipeXml->getParameter("LengthError", Read_LengthError);
    RecipeXml->getParameter("WidthError", Read_WidthError);
    RecipeXml->getParameter("Diagonal1Error", Read_Diagonal1Error);
    RecipeXml->getParameter("Diagonal2Error", Read_Diagonal2Error);
}

void RecipeParse::WriteParams()
{
    RecipeXml->setParameter("Length", Read_Length);
    RecipeXml->setParameter("Width", Read_Width);
    RecipeXml->setParameter("Diagonal1", Read_Diagonal1);
    RecipeXml->setParameter("Diagonal2", Read_Diagonal2);

    RecipeXml->setParameter("LengthError", Read_LengthError);
    RecipeXml->setParameter("WidthError", Read_WidthError);
    RecipeXml->setParameter("Diagonal1Error", Read_Diagonal1Error);
    RecipeXml->setParameter("Diagonal2Error", Read_Diagonal2Error);

    RecipeXml->SaveParasToFile();
}
