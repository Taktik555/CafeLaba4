#ifndef RIVERLIST_H
#define RIVERLIST_H

#include <QAbstractListModel>
#include <QVariant>
#include <QList>
#include <QModelIndex>
#include <QItemSelectionModel>
#include "river.h"

class RiverList : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QAbstractListModel* riverModel READ getModel CONSTANT)  /* первый параметр - тип свойства (property)
                                                                     второй параметр - имя свойства, по которому будем обращаться к реальной модели в qml-файле
                                                                     третий параметр - метод С++ для получения значения свойства (получим саму модель)
                                                                     CONSTANT - qml получит свойство однократно, и в процессе работы это свойство изменяться не будет */
private:
    QList<River> listOfRivers; // непосредственно данные
    QAbstractListModel *getModel();

public:
    RiverList(QObject *parent = nullptr);
    ~RiverList() override;

    // количество колонок
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

     // возвращение данных модели по указанному индексу и роли
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    enum ResentRoles {
            name = Qt::DisplayRole,
            lenght = Qt::DisplayRole + 1,
            flow = Qt::DisplayRole + 2,
            runoff = Qt::DisplayRole + 3,
            area = Qt::DisplayRole + 4
       };

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void add(const QString& nameRiv, const QString& lenghtRiv, const QString& flowRiv, const QString& runoffRiv, const QString& areaRiv);  // макрос указывает, что к методу можно обратиться из QML
    Q_INVOKABLE void del(const int index);
    Q_INVOKABLE QString count(const QString& textSelArea);
    Q_INVOKABLE void edit(const QString& nameRiv, const QString& lenghtRiv, const QString& flowRiv, const QString& runoffRiv, const QString& areaRiv, const int index);
};

#endif // RIVERLIST_H
