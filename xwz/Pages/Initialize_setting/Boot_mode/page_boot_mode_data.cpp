#include "page_boot_mode_data.h"
#include "dev_config.h"


#include <QRegExp>
#include <QDebug>
#include <QJsonValueRef>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include <unistd.h>

Page_boot_mode_data::
Page_boot_mode_data(QObject *parent):QObject(parent)
{
    Dev_config config ;
    m_boot_mode = config.m_boot_mode;
    m_mode_shutdown = config.m_mode_shutdown;

    m_tim = new QTimer(this);
    connect( m_tim,SIGNAL(timeout()),this,SLOT(slot_timer()));
    m_tim->start(500);
}

Page_boot_mode_data::
~Page_boot_mode_data()
{
    if ( m_modify_counter > 0 ){
        Dev_config config;
        config.save_boot_mode( QString("setting.json"),m_boot_mode );
    }
}

void Page_boot_mode_data::
slot_timer()
{
   emit boot_mode_changed( m_boot_mode );
   m_tim->stop();
}

void Page_boot_mode_data::
p_mode_clicked()
{
    if ( m_boot_mode != 0 ){
        m_boot_mode = 0;
        m_modify_counter++;
        emit boot_mode_changed( m_boot_mode );
    }
}

void Page_boot_mode_data::
e_mode_clicked()
{
    if ( m_boot_mode != 1 ){
        m_boot_mode = 1;
        m_modify_counter++;
        emit boot_mode_changed( m_boot_mode );
    }
}

void Page_boot_mode_data::
last_mode_clicked()
{
    if ( m_boot_mode != 2 ){
        m_boot_mode = 2;
        m_modify_counter++;
        emit boot_mode_changed( m_boot_mode );
    }
}
