#include "riverlist.h"
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
#include <QApplication>

RiverList::RiverList(QObject* parent):QAbstractListModel(parent)
{
    add("Речка 1", "100", "В Черное Море", "большой", "1000");
    add("Речка 2", "200", "В Черное Море", "средний", "501");
    add("Речка 2", "300", "В Черное Море", "маленький", "1030");
}

RiverList::~RiverList()
{

}

int RiverList::rowCount(const QModelIndex&) const //число элементов в data
{
    return listOfRivers.size();
}


QVariant RiverList::data(const QModelIndex &index, int role) const //возвращает данные элемента
{
    if (index.row() < 0 || index.row() >= listOfRivers.size())
            return QVariant();
      {
        switch (role) {
                case name:
                    return QVariant(listOfRivers.at(index.row()).getName());
                case lenght:
                    return QVariant(listOfRivers.at(index.row()).getLenght());
                case flow:
                    return QVariant(listOfRivers.at(index.row()).getFlow());
                case runoff:
                    return QVariant(listOfRivers.at(index.row()).getRunoff());
                case area:
                    return QVariant(listOfRivers.at(index.row()).getArea());

                default:
                    return QVariant();
            }

    }
}

QHash<int, QByteArray> RiverList::roleNames() const //возвращает список ролей, доступных в делегате
{
    QHash<int, QByteArray> roles; //элементы произвольно упорядочиваются + происходит оч быстрый поиск значения, связанного с ключом
    roles[name] = "nameOfRiver";
    roles[lenght] = "lenghtOfRiver";
    roles[flow] = "flowOfRiver";
    roles[runoff] = "runoffOfRiver";
    roles[area] = "areaOfRiver";
       return roles;
}

void RiverList::add(const QString& nameRiv, const QString& lenghtRiv, const QString& flowRiv, const QString& runoffRiv, const QString& areaRiv){
     River river;
     river.setName(nameRiv);
     river.setLenght(lenghtRiv);
     river.setFlow(flowRiv);
     river.setRunoff(runoffRiv);
     river.setArea(areaRiv);

    beginInsertRows(QModelIndex(),listOfRivers.size(),listOfRivers.size()); //издаст нужные сигналы о том что готовится добавление элементов
    listOfRivers.append(river);  //добавление в конец списка
    endInsertRows(); //издаёт сигнал о том что в модель добавились элементы
}

QAbstractListModel* RiverList::getModel()
{
    return this;
}

void RiverList::del(const int index)
{

     if (index >= 0 && index < listOfRivers.size())
     {

    // сообщение модели о процессе удаления данных
         beginRemoveRows(QModelIndex(), index, index);
        listOfRivers.removeAt(index);
              endRemoveRows();
     }
     //else qDebug() << "Error index";

}

QString RiverList::count(const QString& textSelArea){ //считаем речки, полощадь бассейна которых больше указанного числа
    int count = 0;
    for(int i = 0; i < listOfRivers.size(); i++)
    {

        QString temp = listOfRivers[i].getLenght();
        if(textSelArea < temp)
            count++;
    }
    QString c = QString::number(count);
    return c;
}

void RiverList::edit(const QString& nameRiv, const QString& lenghtRiv, const QString& flowRiv, const QString& runoffRiv, const QString& areaRiv, const int index) {
     if(index >= 0 && index < listOfRivers.size() )
     {
        auto& currentRiver = listOfRivers[index];
        if (currentRiver.getName().compare(nameRiv)!=0 || currentRiver.getLenght() != lenghtRiv || currentRiver.getFlow() != flowRiv
                || currentRiver.getRunoff() != runoffRiv || currentRiver.getArea() != areaRiv)
        {
            currentRiver.setName(nameRiv);
            currentRiver.setLenght(lenghtRiv);
            currentRiver.setFlow(flowRiv);
            currentRiver.setRunoff(runoffRiv);
            currentRiver.setArea(areaRiv);

            auto modelIndex = createIndex(index, 0); //создавать индексы моделей для использования другими компонентами
            emit dataChanged(modelIndex, modelIndex); //выдается всякий раз, когда изменяются элементы данных, предоставляемые моделью
            //qDebug() << listOfRivers[index].getArea();
        }

     }
      //else qDebug() << "Error index";
}
