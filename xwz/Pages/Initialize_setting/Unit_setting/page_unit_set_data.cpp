#include "page_unit_set_data.h"
#include "../Boot_mode/dev_config.h"
#include "../dev_configuration.h"

#include <QRegExp>
#include <QDebug>
#include <QJsonValueRef>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <unistd.h>

Page_unit_set_data::
Page_unit_set_data(QObject *parent):QObject(parent)
{
    QString str;
    int ret = Dev_configuration::get_key_val(QString("setting.json"),QString("units"), &str);
    if ( ret == 0 ){
        if ( str == "si" ){
            m_units = 0;
        } else if ( str == "me" ){
            m_units = 1;
        } else if ( str == "im" ){
            m_units = 2;
        }
    }
    m_tim = new QTimer(this);
    connect( m_tim,SIGNAL(timeout()),this,SLOT(slot_timer()));
    m_tim->start(200);
}

Page_unit_set_data::
~Page_unit_set_data()
{
    if ( m_modify_counter > 0 ){
         QString str;
         if ( m_units == 0 ){
             str = "si";
         } else if ( m_units == 1 ){
             str = "me";
         } else if ( m_units == 2 ){
             str = "im";
         }
         Dev_configuration::set_key_val(QString("setting.json"),QString("units"), str);
    }
}

void Page_unit_set_data::
slot_timer()
{
   emit units_changed( m_units );
   m_tim->stop();
}

void Page_unit_set_data::
si_units_clicked()
{
    if ( m_units != 0 ){
        m_units = 0;
        m_modify_counter++;
        emit units_changed( m_units );
    }
}

void Page_unit_set_data::
metric_units_clicked()
{
    if ( m_units != 1 ){
        m_units = 1;
        m_modify_counter++;
        emit units_changed( m_units );
    }
}

void Page_unit_set_data::
imperial_units_clicked()
{
    if ( m_units != 2 ){
        m_units = 2;
        m_modify_counter++;
        emit units_changed( m_units );
    }
}
