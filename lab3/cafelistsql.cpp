#include "cafelistsql.h"
#include "QObject"

cafelistsql::cafelistsql(QObject *parent) :
    QSqlQueryModel(parent)
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./CafeDB.db");


     _isConnectionOpen = true;

    if(!db.open())
    {
        qDebug() << db.lastError().text();
        _isConnectionOpen = false;
    }


    QSqlQuery qry(db);
    qry.prepare("CREATE TABLE IF NOT EXISTS CafeList (Id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, nameOfCafe text, lenghtOfCafe text, flowOfCafe text,runoffOfCafe text, Id_cafe integer)");
    if( !qry.exec() )
    {
        qDebug() << db.lastError().text();
        _isConnectionOpen = false;
    }

    refresh();
}

QSqlQueryModel* cafelistsql::getModel(){
    return this;
}
bool cafelistsql::isConnectionOpen(){
    return _isConnectionOpen;
}
QHash<int, QByteArray> cafelistsql::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "nameOfCafe";
    roles[Qt::UserRole + 2] = "lenghtOfCafe";
    roles[Qt::UserRole + 3] = "flowOfCafe";
    roles[Qt::UserRole + 4] = "runoffOfCafe";
    roles[Qt::UserRole + 6] = "Id";
    return roles;
}


QVariant cafelistsql::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if(role < Qt::UserRole-1)
    {
        value = QSqlQueryModel::data(index, role);
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }
    return value;
}

const char* cafelistsql::SQL_SELECT =
        "SELECT nameOfCafe,lenghtOfCafe,flowOfCafe,runoffOfCafe, Id"
        " FROM CafeList";

void cafelistsql::refresh()
{
    this->setQuery(cafelistsql::SQL_SELECT,db);
}

void cafelistsql::add(const QString& nameRiv, const QString& lenghtRiv, const QString& flowRiv, const QString& runoffRiv){

    QSqlQuery query(db);
    QString phQuery= QString("INSERT INTO CafeList (nameOfCafe,lenghtOfCafe,flowOfCafe,runoffOfCafe) VALUES ('%1', '%2', '%3', '%4')")
            .arg(nameRiv)
            .arg(lenghtRiv)
            .arg(flowRiv)
            .arg(runoffRiv);
    query.exec(phQuery);

    refresh();

}

void cafelistsql::edit(const QString& nameRiv, const QString& lenghtRiv, const QString& flowRiv, const QString& runoffRiv, const int index){

    QSqlQuery query(db);
    QString phQuery= QString("UPDATE CafeList SET nameOfCafe = '%1',lenghtOfCafe = '%2',flowOfCafe = %3, runoffOfCafe = %4, WHERE Id = %5")
            .arg(nameRiv)
            .arg(lenghtRiv)
            .arg(flowRiv)
            .arg(runoffRiv)
            .arg(index);
    query.exec(phQuery);

    refresh();

}
void cafelistsql::del(const int Id){


    QSqlQuery query(db);
    QString strQuery= QString("DELETE FROM CafeList WHERE Id = %1")
            .arg(Id);
    query.exec(strQuery);

    refresh();
}

QString cafelistsql::count(const QString& textCount){

    QSqlQuery query(db);
    QString phQuery= QString("SELECT COUNT (Id) FROM CafeList WHERE circulation <= %1")
            .arg(textCount.toInt());
    query.exec(phQuery);

    QString info;
    while(query.next())
    {
        info = query.value(0).toString();

    }
    return(info);

}
