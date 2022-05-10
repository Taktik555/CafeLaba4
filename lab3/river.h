#ifndef RIVER_H
#define RIVER_H
#include "QString"
//#include <QObject>

class River /*public QObject*/
{
    //Q_OBJECT

public:
    River(/*QString ID, QString Name, QString Flow, QString Lenght, QString Runoff, QString Area QObject *parent = nullptr */);
    virtual ~River();
    void setID(const QString ID);
    void setName(const QString Name);
    void setFlow(const QString Flow);
    void setLenght(const QString Lenght);
    void setRunoff(const QString Runoff);
    void setArea(const QString Area);

    QString getID() const;
    QString getName() const;
    QString getFlow() const;
    QString getLenght() const;
    QString getRunoff() const;
    QString getArea() const;

private:
    QString id;
    QString name; //название
    QString lenght; //протяженность
    QString flow; //куда впадает
    QString runoff; //годовой сток
    QString area; //площадь бассейна
};

#endif // RIVER_H
