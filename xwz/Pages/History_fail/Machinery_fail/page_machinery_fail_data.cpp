#include "page_machinery_fail_data.h"
#include <QDebug>

Page_machinery_fail_data::
Page_machinery_fail_data(QObject *parent):
    QObject(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./fail.db");
    if(!db.open()){
        qDebug("open is false");
    }else{
        qDebug("open is OK");
    }
    m_fail_data_model = new Dev_fail_record(1,this);
}

/// 返回四个子页面的模型
Dev_fail_record* Page_machinery_fail_data::
get_fail_data_model(void)
{
    return m_fail_data_model;
}
