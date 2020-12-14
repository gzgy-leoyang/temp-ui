#include "page_function_data.h"


#include <QRegExp>
#include <QDebug>
#include <QJsonValueRef>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include <unistd.h>

Page_function_data::
Page_function_data(QObject *parent):QObject(parent)
{
    m_auto_lock = 0; //m_auto_lock = g_can_data->get( _AUTO_LOCK_SATATUS );
    if ( m_auto_lock == 1 ){
        emit auto_lock_changed( QString("开启") );
    } else {
        emit auto_lock_changed( QString("未开启") );
    }

    m_cmd_lock = 0; //m_cmd_lock = g_can_data->get( _CMD_LOCK_SATATUS );
    if ( m_cmd_lock == 1 ){
        emit cmd_lock_changed( QString("开启") );
    } else {
        emit cmd_lock_changed( QString("未开启") );
    }


    m_timer = new QTimer(this);
    connect( m_timer,SIGNAL(timeout()),this,SLOT(slot_timer()));
    m_timer->start(200);
}

Page_function_data::
~Page_function_data()
{

}

void Page_function_data::
slot_timer()
{
    /// 实际使用如下代码:读取状态,发送变化量
    /*
    int val = g_can_data->get( _AUTO_LOCK_SATATUS );
    if ( val != m_auto_lock ){
        m_auto_lock = val ;
        if ( m_auto_lock == 1 ){
            emit auto_lock_changed( QString("开启") );
        } else {
            emit auto_lock_changed( QString("未开启") );
        }
    }

    val = g_can_data->get( _CMD_LOCK_SATATUS );
    if ( val != m_cmd_lock ){
        m_cmd_lock = val ;
        if ( m_cmd_lock == 1 ){
            emit cmd_lock_changed( QString("开启") );
        } else {
            emit cmd_lock_changed( QString("未开启") );
        }
    }
    */
}

QString Page_function_data::
get_auto_lock( void ) const
{
    if ( m_auto_lock == 1 ){
        return QString("开启");
    } else {
        return QString("未开启");
    }
}

void Page_function_data::
auto_lock_clicked()
{
   if ( m_auto_lock == 1 ) {
       set_auto_lock_cmd( 0 );

       /// >>>testing
       m_auto_lock = 0;
       emit auto_lock_changed( QString("未开启") );
       /// <<<testing
   } else {
       set_auto_lock_cmd( 1 );

       /// >>>testing
       m_auto_lock = 1;
       emit auto_lock_changed( QString("开启") );
       /// <<<testing
   }
}

int Page_function_data::set_auto_lock_cmd( const int& _val )
{
    QList<int> list;
    for ( int i=0;i<8;i++ ){
        list += 0;
    }
//    g_dev_can->transmit_frame( 0x18FF0928,1,list );
    return 0;
}

////////
QString Page_function_data::
get_cmd_lock( void ) const
{
    if ( m_cmd_lock == 1 ){
        return QString("开启");
    } else {
        return QString("未开启");
    }
}

void Page_function_data::
cmd_lock_clicked()
{
   if ( m_cmd_lock == 1 ) {
       set_cmd_lock_cmd( 0 );

       /// >>>testing
       m_cmd_lock = 0;
       emit cmd_lock_changed( QString("未开启") );
       /// <<<testing
   } else {
       set_cmd_lock_cmd( 1 );

       /// >>>testing
       m_cmd_lock = 1;
       emit cmd_lock_changed( QString("开启") );
       /// <<<testing
   }
}

int Page_function_data::
set_cmd_lock_cmd( const int& _val )
{
    QList<int> list;
    for ( int i=0;i<8;i++ ){
        list += 0;
    }
//    g_dev_can->transmit_frame( 0x18FF0931,1,list );
    return 0;
}

////////////////
