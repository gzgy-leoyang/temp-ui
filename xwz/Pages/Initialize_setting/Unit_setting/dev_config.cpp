#include "dev_config.h"

#include <QRegExp>
#include <QDebug>
#include <QJsonValueRef>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include <unistd.h>

Dev_config::
Dev_config(QObject *parent) : QObject(parent)
{
    load_config( QString("setting.json"));
}

///启动就需要发出一次模式命令
void Dev_config::
set_work_mode_booting(void)
{
    if ( m_boot_mode < 2 ){
        /// 0=P,1=E
        set_boot_mode_cmd( m_boot_mode );
    } else {
        /// 2=last
        if ( m_mode_shutdown == "p" ){
            set_boot_mode_cmd( 0 );

        } else if ( m_mode_shutdown == "e" ){
            set_boot_mode_cmd( 1 );
        }
    }
}

int Dev_config::
set_boot_mode_cmd( const int& _val )
{
    qDebug()<<"SEND [WORK MODE] COMMAND TO ECU/VCU ";
    qDebug()<<"Dev_config::set_boot_mode_cmd"<<_val;
//    QList<int> list;
//    for ( int i=0;i<8;i++ ){
//        list += 0;
//    }
//    list[x] = cmd;
//    g_dev_can->transmit_frame( 0x18FF0931,1,list );
    return 0;
}

int Dev_config::
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

        init_json_obj.insert("boot_mode", QJsonValue(0));
        init_json_obj.insert("work_mode_shutdown", QJsonValue("p"));

        QJsonDocument init_docu(init_json_obj);
        file.write(init_docu.toJson());
        file.close();
        return -1;
    }

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        m_boot_mode = 0;
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

    if(json_obj.contains("work_mode_shutdown")){
        m_mode_shutdown = json_obj.value("work_mode_shutdown").toString();
    } else {
        m_mode_shutdown = "p";
    }

    if(json_obj.contains("boot_mode")){
        m_boot_mode = json_obj.value("boot_mode").toInt();

        if ( m_boot_mode > 2 )
            m_boot_mode = 2;
        else if ( m_boot_mode < 0 )
            m_boot_mode = 0;
    } else {
        m_boot_mode = 0;
    }

    return 0;
}


/*
    // 读取钥匙开关信号
    QFile f("/sys/class/gpio/gpio37/value");
    if ( !f.exists() ){
        Debug::log( _DEBUG_ERROR,LIGHT_RED "/sys/class/gpio/gpio37/value is NOT EXIST" NONE);
        return ;
    }

    if (! f.open(QIODevice::ReadOnly | QIODevice::Text)){
        Debug::log( _DEBUG_ERROR,LIGHT_RED "/sys/class/gpio/gpio37/value could NOT OPEN" NONE);
        return ;
    }

    QTextStream in(&f);
    QString key_status = in.readLine();
    f.close();

    if ( key_status == "1" ){
        p_current = 1;
    } else if ( key_status == "0" ){
        p_current = 0;
        /// 关闭钥匙开关
    }
*/
/// 关机时需要保存一次工作模式
int Dev_config::
save_work_mode_shutdown( QString _file_name,int _mode )
{
    QString mode = "";
    /// 关机保存,只能是0(P),1(E)
    if ( _mode == 0 ){
        mode = "p";
    } else if ( _mode == 1 ){
        mode = "e";
    } else {
        mode = "p";
    }

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
    ite = json_obj.find("work_mode_shutdown");
    if ( ite != json_obj.end() ){
        QJsonValueRef ref = ite.value();
        ref = QJsonValue( mode );
    }

    json_docu.setObject(json_obj);
    file.write(json_docu.toJson());
    file.close();
    sync();
    qDebug()<<"SAVE [WORK MODE WHEN SHUTDOWN] TO setting.json ";
    return 0;
}


int Dev_config::
save_boot_mode( QString fileName,int _boot_mode )
{
    QJsonObject     json_obj;
    QJsonParseError json_err;
    if(fileName == ""){
        return -1;
    }
    if ( _boot_mode > 2 ){
        _boot_mode = 2;
    }

    if ( _boot_mode < 0 ){
        _boot_mode = 0;
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
    ite = json_obj.find("boot_mode");
    if ( ite != json_obj.end() ){
        QJsonValueRef ref = ite.value();
        ref = QJsonValue( _boot_mode );
    }

    json_docu.setObject(json_obj);
    file.write(json_docu.toJson());
    file.close();
    sync();
    qDebug()<<"SAVE [WORK MODE] TO setting.json ";
    return 0;
}
