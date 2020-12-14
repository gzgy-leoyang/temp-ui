#include "page_setting_data.h"


#include <QRegExp>
#include <QDebug>
#include <QJsonValueRef>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include <unistd.h>

Page_setting_data::
Page_setting_data(QObject *parent):QObject(parent)
{
    m_idle_delay = 2;
    m_coolant_comp = 0;
    m_hydraulic_comp = 0;
    m_modify_counter = 0;

    load_config( "setting.json" );
}

Page_setting_data::
~Page_setting_data()
{
    if ( m_modify_counter > 0 ){
        save_config( "setting.json" );
    }
}

QString Page_setting_data::
get_idle_delay( void ) const
{
    return (QString::number( m_idle_delay ) + "s");
}

void Page_setting_data::
set_idle_delay( QString _val )
{
    QRegExp rx("^([0-9]{1})$");
    if ( rx.isValid() ){
        if ( rx.exactMatch( _val ) ){
            m_modify_counter++;
            int temp = _val.toInt() ;
            if ( temp > 7 ){
                temp = 7;
            } else  if ( temp < 2 ){
                temp = 2;
            }
            m_idle_delay = temp;
        }
    }
}

QString Page_setting_data::
get_coolant_comp( void ) const
{
    return (QString::number( m_coolant_comp ) + "℃");
}

void Page_setting_data::
set_coolant_comp( QString _val )
{
    QRegExp rx("^(-?[0-9]{1,2})$");
    if ( rx.isValid() ){
        if ( rx.exactMatch( _val ) ){
            int temp = _val.toInt() ;
            if ( temp > 15 ){
                temp = 15;
            } else  if ( temp < -15 ){
                temp = -15;
            }
            m_coolant_comp = temp ;
            m_modify_counter++;

        }
    }
}

QString Page_setting_data::
get_hydraulic_comp( void ) const
{
    return (QString::number( m_hydraulic_comp ) + "℃");
}

void Page_setting_data::
set_hydraulic_comp( QString _val )
{
    QRegExp rx("^(-?[0-9]{1,2})$");
    if ( rx.isValid() ){
        if ( rx.exactMatch( _val ) ){
            int temp = _val.toInt() ;
            if ( temp > 15 ){
                temp = 15;
            } else  if ( temp < -15 ){
                temp = -15;
            }
            m_hydraulic_comp = temp;
            m_modify_counter++;
        }
    }
}


int Page_setting_data::set_idle_delay_cmd( const int& _val )
{
    QList<int> list;
    for ( int i=0;i<8;i++ ){
        list += 0;
    }
//    g_dev_can->transmit_frame( 0x18FF2080,1,list );
    return 0;
}

int Page_setting_data::set_coolant_comp_cmd( const int& _val )
{
    QList<int> list;
    for ( int i=0;i<8;i++ ){
        list += 0;
    }
//    g_dev_can->transmit_frame( 0x18FF2080,1,list );
    return 0;
}

int Page_setting_data::set_hydraulic_comp_cmd( const int& _val )
{
    QList<int> list;
    for ( int i=0;i<8;i++ ){
        list += 0;
    }
//    g_dev_can->transmit_frame( 0x18FF2080,1,list );
    return 0;
}

int Page_setting_data::
load_config(const QString& fileName)
{
    if(fileName == ""){
        return -1;
    }
    QFile file(fileName);

    //若文件不存在，则初始化、创建json文件
    if(!file.exists()){
        m_idle_delay = 2;
        m_coolant_comp = 0;
        m_hydraulic_comp = 0;

        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QJsonObject init_json_obj;

        init_json_obj.insert("idle_delay", QJsonValue(2));
        init_json_obj.insert("coolant_temp_comp", QJsonValue(0));
        init_json_obj.insert("hydraulic_temp_comp", QJsonValue(0));

        QJsonDocument init_docu(init_json_obj);
        file.write(init_docu.toJson());
        file.close();
        return -1;
    }

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        m_idle_delay = 2;
        m_coolant_comp = 0;
        m_hydraulic_comp = 0;
        return -1;
    }

    QString file_content = file.readAll();
    file.close();

    QJsonParseError json_err;
    QJsonDocument json_docu = QJsonDocument::fromJson(file_content.toUtf8(), &json_err);
    if(json_err.error != QJsonParseError::NoError){
        return -1;
    }

    if(!json_docu.isObject()){
        return -1;
    }

    QJsonObject json_obj = json_docu.object();

    if(json_obj.contains("idle_delay")){
        int temp = json_obj.value("idle_delay").toInt();
        if(temp < 2)
            temp = 2;
        else if(temp > 7)
            temp = 7;
        m_idle_delay = temp;
    }

    if(json_obj.contains("coolant_temp_comp")){
        int temp = json_obj.value("coolant_temp_comp").toInt();
        if(temp < -15)
            temp = -15;
        else if(temp > 15)
            temp = 15;
        m_coolant_comp = temp;
    }

    if(json_obj.contains("hydraulic_temp_comp")){
        int temp = json_obj.value("hydraulic_temp_comp").toInt();
        if(temp < -15)
            temp = -15;
        else if(temp > 15)
            temp = 15;
        m_hydraulic_comp = temp;
    }

    return 0;
}

int Page_setting_data::
save_config(QString fileName)
{
    QJsonObject     json_obj;
    QJsonParseError json_err;
    if(fileName == ""){
        return -1;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        return -2;
    }

    QString file_content = file.readAll();
    file.resize(0);

    QJsonDocument json_docu = QJsonDocument::fromJson(file_content.toUtf8(), &json_err);
    if(json_err.error != QJsonParseError::NoError){
        file.close();
        return -3;
    }
    json_obj = json_docu.object();

    QJsonObject::iterator ite;
    ite = json_obj.find("idle_delay");
    if ( ite != json_obj.end() ){
        QJsonValueRef ref = ite.value();
        ref = QJsonValue(m_idle_delay);
    }

    ite = json_obj.find("coolant_temp_comp");
    if ( ite != json_obj.end() ){
        QJsonValueRef ref = ite.value();
        ref = QJsonValue(m_coolant_comp);
    }

    ite = json_obj.find("hydraulic_temp_comp");
    if ( ite != json_obj.end() ){
        QJsonValueRef ref = ite.value();
        ref = QJsonValue(m_hydraulic_comp);
    }

    json_docu.setObject(json_obj);
    file.write(json_docu.toJson());
    file.close();
    sync();
    return 0;
}
