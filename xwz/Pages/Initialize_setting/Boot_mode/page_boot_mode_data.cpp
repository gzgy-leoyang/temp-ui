#include "page_boot_mode_data.h"
#include "../dev_configuration.h"


#include <QRegExp>
#include <QDebug>
#include <QJsonValueRef>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include <unistd.h>

/*
    // 读取钥匙开关信号
    QFile f("/sys/class/gpio/gpio37/value");
    if ( !f.exists() ){
        return ;
    }

    if (! f.open(QIODevice::ReadOnly | QIODevice::Text)){
        return ;
    }

    QTextStream in(&f);
    QString key_status = in.readLine();
    f.close();

    if ( key_status == "1" ){
        p_current = 1;
    } else if ( key_status == "0" ){
        p_current = 0;
    }

    Dev_configuration::set_key_val(QString("setting.json"),QString("work_mode_shutdown"), str);
    /// "work_mode_shutdown": "p/e"
*/

Page_boot_mode_data::
Page_boot_mode_data(QObject *parent):QObject(parent)
{
    QString str;
    int ret = Dev_configuration::get_key_val(QString("setting.json"),QString("boot_mode"), &str);
    if ( ret == 0 ){
        if ( str == "p" ){
            m_boot_mode = 0;
        } else if ( str == "e" ){
            m_boot_mode = 1;
        } else if ( str == "last" ){
            m_boot_mode = 2;
        }
    } else {
        m_boot_mode = 1;
    }

    m_tim = new QTimer(this);
    connect( m_tim,SIGNAL(timeout()),this,SLOT(slot_timer()));
    m_tim->start(200);
}

Page_boot_mode_data::
~Page_boot_mode_data()
{
    if ( m_modify_counter > 0 ){
        QString str;
        if ( m_boot_mode == 0 ){
            str = "p";
        } else if ( m_boot_mode == 1 ){
            str = "e";
        } else if ( m_boot_mode == 2 ){
            str = "last";
        }
        Dev_configuration::set_key_val(QString("setting.json"),QString("boot_mode"), str);
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
