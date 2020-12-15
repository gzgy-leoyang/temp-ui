#include "dev_configuration.h"

#include <QRegExp>
#include <QDebug>
#include <QJsonValueRef>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include <unistd.h>

Dev_configuration::
Dev_configuration(QObject *parent) : QObject(parent)
{
}

int  Dev_configuration::
set_key_val( QString _file_name,QString _key,QString _val )
{
    QJsonObject     json_obj;
    QJsonParseError json_err;
    if( _file_name == ""){
        return -1;
    }

    QFile file( _file_name );
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
    ite = json_obj.find( _key );
    if ( ite != json_obj.end() ){
        QJsonValueRef ref = ite.value();
        ref = QJsonValue( _val );
    }

    json_docu.setObject(json_obj);
    file.write(json_docu.toJson());
    file.close();
    sync();
    qDebug()<<"SET [ "<<_key<<_val<<" ]To setting.json";
    return 0;
}

int  Dev_configuration::
get_key_val( QString _file_name,QString _key,QString* _val )
{
    if( _file_name == ""){
        return -1;
    }

    QFile file(_file_name);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
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
    if(json_obj.contains(_key)){
        QString val = json_obj.value( _key ).toString();
        *_val = val;
        qDebug()<<"GET [ "<<_key<<val<<" ]Form setting.json";
        return 0;
    } else {
        *_val =  "";
        return -1;
    }
}
