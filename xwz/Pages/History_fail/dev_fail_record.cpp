#include "dev_fail_record.h"
#include <QDebug>

/// 模型>>>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

/// 链接数据库中的内容字段与ListView delegate 中的内容标记
/// 修改字段,对应的显示内容修改,此处必须对应修改
const char* Dev_fail_record::COLUMN_NAMES[] = {
    "content",
    "hour",
    NULL
};

/// 查询语句,对应数据库字段和具体的表
const char* Dev_fail_record::SQL_SELECT_ELECTRICAL =
    "SELECT content,hour"
    " FROM table_electrical";
const char* Dev_fail_record::SQL_SELECT_MACHINERY =
    "SELECT content,hour"
    " FROM table_machinery";
const char* Dev_fail_record::SQL_SELECT_ENGINE =
    "SELECT content,hour"
    " FROM table_engine";


/// 模型>>>
Dev_fail_record::Dev_fail_record(QObject *parent) :
    QSqlQueryModel(parent)
{
    /// 数据字段 <---> ListView delegate
    hash = new QHash<int,QByteArray>;
    hash->insert(Qt::UserRole,      QByteArray("content"));
    hash->insert(Qt::UserRole + 1,  QByteArray("hour"));
    refresh();
}

Dev_fail_record::Dev_fail_record( int _table,QObject *parent) :
    QSqlQueryModel(parent)
{
    m_table_index = _table;
    /// 数据字段 <---> ListView delegate
    hash = new QHash<int,QByteArray>;
    hash->insert(Qt::UserRole,      QByteArray("content"));
    hash->insert(Qt::UserRole + 1,  QByteArray("hour"));
    refresh();
}

void Dev_fail_record::refresh()
{
    //sql查询
    switch(m_table_index){
    case 0:
        this->setQuery(SQL_SELECT_ELECTRICAL);
        break;
    case 1:
        this->setQuery(SQL_SELECT_MACHINERY);
        break;
    case 2:
        this->setQuery(SQL_SELECT_ENGINE);
        break;
    }
}

QHash<int, QByteArray> Dev_fail_record::roleNames() const
{
    return *hash;
}

QVariant Dev_fail_record::data(const QModelIndex &index, int role) const
{
    if(role < Qt::UserRole) {
       return QSqlQueryModel::data(index, role);
    }
    QSqlRecord r = record(index.row());
    return r.value(QString(hash->value(role))).toString();
}
/// 模型 <<<
