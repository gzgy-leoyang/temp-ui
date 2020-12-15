#include "page_machine_info_data.h"
#include "../dev_configuration.h"

#include <QRegExp>
#include <QDebug>
#include <QJsonValueRef>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include <unistd.h>

Page_machine_info_data::
Page_machine_info_data(QObject *parent):QObject(parent)
{
    QString str;
    int ret = Dev_configuration::get_key_val(QString("setting.json"),QString("machine_model"), &str);
    if ( ret == 0 ){
        m_machine_model = str;
    }

    ret = Dev_configuration::get_key_val(QString("setting.json"),QString("machine_sn"), &str);
    if ( ret == 0 ){
        m_machine_sn = str;
    }
}

Page_machine_info_data::
~Page_machine_info_data()
{
}


QString Page_machine_info_data::
get_machine_model( void ) const
{
    return m_machine_model;
}

void Page_machine_info_data::
set_machine_model( QString _val )
{
    if ( _val != m_machine_model ){
        m_machine_model = _val;
        Dev_configuration::set_key_val(QString("setting.json"),QString("machine_model"), _val);
        emit machine_model_changed( m_machine_model );
    }
}

QString Page_machine_info_data::
get_machine_sn( void ) const
{
    return m_machine_sn;
}

void Page_machine_info_data::
set_machine_sn( QString _val )
{
    if ( _val != m_machine_sn ){
        m_machine_sn = _val;
        Dev_configuration::set_key_val(QString("setting.json"),QString("machine_sn"), _val);
        emit machine_sn_changed( m_machine_sn );
    }
}
