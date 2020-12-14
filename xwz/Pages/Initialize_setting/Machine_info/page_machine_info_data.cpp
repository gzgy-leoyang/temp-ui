#include "page_machine_info_data.h"


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
    m_machine_model = "aa";
    m_machine_sn = "000";
    m_modify_counter = 0;

    load_config( "setting.json" );
}

Page_machine_info_data::
~Page_machine_info_data()
{
    if ( m_modify_counter > 0 ){
        qDebug()<<"~Page_machine_info_data...save_config";
        save_config( "setting.json" );
    }
}


QString Page_machine_info_data::
get_machine_model( void ) const
{
    return m_machine_model;
}

void Page_machine_info_data::
set_machine_model( QString _val )
{
    m_machine_model = _val;
    qDebug()<<"set_machine_model..."<<_val;
    m_modify_counter++;
}

QString Page_machine_info_data::
get_machine_sn( void ) const
{
    return m_machine_sn;
}

void Page_machine_info_data::
set_machine_sn( QString _val )
{
    m_machine_sn = _val;
    m_modify_counter++;
}

int Page_machine_info_data::
load_config(const QString& fileName)
{
    if(fileName == ""){
        return -1;
    }
    QFile file(fileName);

    //若文件不存在，则初始化、创建json文件
    if(!file.exists()){
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QJsonObject init_json_obj;

        init_json_obj.insert("machine_model", QJsonValue(0));
        init_json_obj.insert("machine_sn", QJsonValue(0));

        QJsonDocument init_docu(init_json_obj);
        file.write(init_docu.toJson());
        file.close();
        return -1;
    }

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        m_machine_model = "aa";
        m_machine_sn = "000";
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

    if(json_obj.contains("machine_model")){
        m_machine_model = json_obj.value("machine_model").toString();
    } else {
        m_machine_model = "machine_model";
    }

    if(json_obj.contains("machine_sn")){
        m_machine_sn = json_obj.value("machine_sn").toString();
    } else {
        m_machine_sn = "0123456789";
    }
    return 0;
}

int Page_machine_info_data::
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
    ite = json_obj.find("machine_model");
    if ( ite != json_obj.end() ){
        QJsonValueRef ref = ite.value();
        ref = QJsonValue( m_machine_model );
    }

    ite = json_obj.find("machine_sn");
    if ( ite != json_obj.end() ){
        QJsonValueRef ref = ite.value();
        ref = QJsonValue( m_machine_sn );
    }

    json_docu.setObject(json_obj);
    file.write(json_docu.toJson());
    file.close();
    sync();
    return 0;
}
