#ifndef DEV_FAIL_RECORD_H
#define DEV_FAIL_RECORD_H

#include <QObject>
#include <string.h>
#include <QTimer>
#include <QStringList>
#include <QAbstractListModel>
#include <QFile>

/// 模型>>>
#include <QSqlQueryModel>

class Dev_fail_record : public QSqlQueryModel
{
    Q_OBJECT
    QHash<int,QByteArray> *hash;
public:
    explicit Dev_fail_record(QObject *parent = 0);
    Dev_fail_record( int _table,QObject *parent=0);
    QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;
    void refresh();

    QHash<int, QByteArray> roleNames() const;

private:
    const static char* COLUMN_NAMES[];
    const static char* SQL_SELECT_ELECTRICAL;
    const static char* SQL_SELECT_MACHINERY;
    const static char* SQL_SELECT_ENGINE;

    int m_table_index;
};
///  模型<<<


#endif // DEV_FAIL_RECORD_H
