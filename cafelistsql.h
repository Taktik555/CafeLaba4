#ifndef CAFELISTSQL_H
#define CAFELISTSQL_H

#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>

class cafelistsql : public QSqlQueryModel
       {
           Q_OBJECT

           Q_PROPERTY(QSqlQueryModel* cafeModel READ getModel CONSTANT)
           Q_PROPERTY(bool IsConnectionOpen READ isConnectionOpen CONSTANT)

       public:
           explicit cafelistsql(QObject *parent);
           void refresh();
           QHash<int, QByteArray> roleNames() const override;
           QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

           Q_INVOKABLE void add(const QString& nameRiv, const QString& lenghtRiv, const QString& flowRiv, const QString& runoffRiv);  // макрос указывает, что к методу можно обратиться из QML
           Q_INVOKABLE void del(const int Id);
           Q_INVOKABLE QString count(const QString& textSelArea);
           Q_INVOKABLE void edit(const QString& nameRiv, const QString& lenghtRiv, const QString& flowRiv, const QString& runoffRiv, const int Id);

       signals:

       public slots:

       private:
           const static char* SQL_SELECT;
           QSqlDatabase db;
           QSqlQueryModel *getModel();
           bool _isConnectionOpen;
           bool isConnectionOpen();
       };

#endif // CAFELISTSQL_H
