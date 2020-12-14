#include "dev_maintain.h"
#include <unistd.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QDate>

///////////////////////////
Component_entry::
Component_entry(QString _name,int _peroid,double _last,QString _type,QObject* parent) :
    QObject(parent),
    m_type( _type ),
    m_name( _name ),
    m_peroid( _peroid ),
    m_last( _last )
{
}

Component_entry::
Component_entry(QString _name,int _peroid,int _last,QString _type,bool _visible,QString _date,QObject* parent) :
    QObject(parent),
    m_type(_type),
    m_name( _name ),
    m_peroid(_peroid),
    m_last(_last),
    m_visible(_visible),
    m_last_date(_date)
{
}

Maintain_Model::
Maintain_Model(QObject *parent):
    QAbstractListModel( parent )
{
}

void Maintain_Model::
load_maintain_json( QString _file_name ){
        QFile file(_file_name);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "file open failed!";
            return ;
        }
        QString file_content = file.readAll();

        file.close();
        QJsonDocument json_docu = QJsonDocument::fromJson(file_content.toUtf8());
        QJsonObject root_obj = json_docu.object();

        QJsonObject::Iterator iteratorJson;
        iteratorJson = root_obj.begin();
        m_component_list.clear();
        while(iteratorJson != root_obj.end()){
            QJsonObject componten_obj = iteratorJson.value().toObject();
            QString _name   = componten_obj.value("name").toString();
            int     _peroid = componten_obj.value("peroid").toInt();
            double  _last   = componten_obj.value("last").toDouble();
            QString _type   = componten_obj.value("hm_type").toString();
            bool    _visible= componten_obj.value("visible").toBool();
            QString _last_date = componten_obj.value("last_date").toString();
            Component_entry* ce = new Component_entry( _name,_peroid,_last,_type,this);
            ce->m_type = _type;
            ce->m_last = _last;
            ce->m_name = _name;
            ce->m_peroid = _peroid;
            ce->m_visible = _visible;
            ce->m_last_date = _last_date;
            ce->m_color = Qt::lightGray;
            pushData(ce);
            iteratorJson++;
        }
}

void Maintain_Model::
load_maintain_json(QString _file_name,const double& _cur_hour )
{
//    printf("[ demo_ui ]load_maintain_json..0 cur_hour=%d \n",_cur_hour);

    QFile file(_file_name);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
//        Debug::log( _DEBUG_WARRING,RED "file open failed!" NONE);
        qDebug() << "file open failed!";
        return ;
    }
    QString file_content = file.readAll();
    file.close();
    QJsonDocument json_docu = QJsonDocument::fromJson(file_content.toUtf8());
    QJsonObject root_obj = json_docu.object();

    QJsonObject::Iterator iteratorJson;
    iteratorJson = root_obj.begin();
    m_component_list.clear();
    while(iteratorJson != root_obj.end()){
        QJsonObject componten_obj = iteratorJson.value().toObject();
        QString _name   = componten_obj.value("name").toString();
        int     _peroid = componten_obj.value("peroid").toInt();
        double  _last   = componten_obj.value("last").toDouble();
        QString _type   = componten_obj.value("hm_type").toString();
        bool    _visible= componten_obj.value("visible").toBool();
        Component_entry* ce = new Component_entry( _name,_peroid,_last,_type,this);
        ce->m_visible = _visible;
        if(ce->m_visible){
            ce->m_next = (double)_peroid + _last;

            if ( ce->m_next > _cur_hour ){
                ce->m_remaind = ce->m_next - _cur_hour;
                if ( ce->m_remaind < 0.5 ){
                    ce->m_color = Qt::darkCyan;
                } else {
                    ce->m_color = Qt::lightGray;
                }
            } else {
                ce->m_remaind = 0;
                ce->m_color = Qt::darkRed;
            }
            pushData(ce);
        }
        iteratorJson++;
    }
}

int Maintain_Model::
rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_component_list.count();//返回私有列表数据量
}

QVariant Maintain_Model::
data(const QModelIndex &index, int role) const
{
    Component_entry* ce = m_component_list.at(index.row());
    if (role == Qt::UserRole){
        return ce->m_name;
    }
    if (role == Qt::UserRole+1){
        return ce->m_peroid;
    }
    if (role == Qt::UserRole+2){
        return QString::number( ce->m_last,'f',1);
    }
    if (role == Qt::UserRole+3){
        if ( ce->m_remaind != 0 ){
            return QString::number( ce->m_remaind,'f',1);
        } else {
            return QString("--");
        }
    }
    if (role == Qt::UserRole+4){
        return QColor(ce->m_color);
    }
    if (role == Qt::UserRole+5){
        return ce->m_visible;
    }

    return 0;
}


QHash<int, QByteArray> Maintain_Model::
roleNames() const
{
    QHash<int, QByteArray>  hash;
    hash.insert(Qt::UserRole,      QByteArray("title"));
    hash.insert(Qt::UserRole + 1,  QByteArray("cycle"));
    hash.insert(Qt::UserRole + 2,  QByteArray("last_time"));
    hash.insert(Qt::UserRole + 3,  QByteArray("next_countdown"));
    hash.insert(Qt::UserRole + 4,  QByteArray("txt_color"));
    hash.insert(Qt::UserRole + 5,  QByteArray("display"));
    return hash;
}

void Maintain_Model::
set_last( const int& _index ,const double& _val )
{
    Component_entry* ce = m_component_list.at(_index);
    QModelIndex indexxx = index(_index);
    ce->m_last = _val;
    ce->m_remaind = (double)ce->m_peroid;
    if ( ce->m_color != Qt::lightGray )
        ce->m_color = Qt::lightGray;

    emit QAbstractItemModel::dataChanged(indexxx,indexxx);
}

void Maintain_Model::
set_visible( const int& _index ){
    Component_entry* ce = m_component_list.at(_index);
    QModelIndex indexxx = index(_index);
    ce->m_visible = !ce->m_visible;

    emit QAbstractItemModel::dataChanged(indexxx,indexxx);
}

int Maintain_Model::
save_maintain_file(void){
    QFileDevice::Permissions target_file_permission;

    QString target_name_str("maintain.json");
    QString backup_name_str("maintain.json.b");
    QFile target_file( target_name_str );
    QFile backup_file( backup_name_str );

    if ( backup_file.exists() ){
        backup_file.remove();
//        sync();
    }

    if ( target_file.exists() ){
        // replace file
        target_file_permission = QFile::permissions(target_name_str);
        // 保存备份
        if ( ! target_file.copy(backup_name_str) ){
            qDebug() << "Failed to copy maintain.json as maintain.json.b";
        } else {
            qDebug() << "maintain.json Save as maintain.json.b";
        }
        // 删除准备替换的目标文件
        target_file.remove();
//        sync();
    }

    QJsonDocument json_doc;
    QJsonObject root_obj;

    int sizeof_list = m_component_list.count();
    for ( int i=0;i < sizeof_list;i++ ){
        Component_entry* ce = m_component_list.at(i);
        QString date_str = QDate::currentDate().toString("yy-MM-dd");
        ce->m_last_date = date_str;
        QJsonObject cmp_obj;
        cmp_obj.insert("name"   , ce->m_name );
        cmp_obj.insert("peroid" , ce->m_peroid);
        QString str = QString::number( ce->m_last,'f',1);
        double db = str.toDouble();
        cmp_obj.insert("last"   , db );
        cmp_obj.insert("hm_type", ce->m_type);
        cmp_obj.insert("visible", ce->m_visible);
        cmp_obj.insert("last_date", ce->m_last_date);
        root_obj.insert(QString::number(i), QJsonValue( cmp_obj ) );
    }
    json_doc.setObject(root_obj);

    if(!target_file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
    }
    target_file.resize( 0 );
    target_file.write( json_doc.toJson() );
    target_file.close();
    qDebug() << "File save success";
    return 0;
}


bool Maintain_Model::
pushData(Component_entry* _entry)
{
    beginInsertRows(QModelIndex(), m_component_list.count(), m_component_list.count());
    m_component_list.append(_entry);
    endInsertRows();
    return true;
}


Dev_maintain::
Dev_maintain(QObject *parent) : QObject(parent)
{
//    double cur_hour = 30.0;//(double)m_hourmeter_info.idle_hour / 360.0;
    m_model = new Maintain_Model();
//    m_model->load_maintain_json(QString("maintain.json"),cur_hour);
}

int Dev_maintain::
require_factory_init(){
    /// re-load maintance json
    QString maintain_file_name = QString("maintain.json");
    QFile maintain_file(maintain_file_name);
    QFileDevice::Permissions maintain_file_permission = QFile::permissions(maintain_file_name);
    if ( maintain_file.exists() ){
        maintain_file.remove();
        sync();
    }

    QString default_file_name = QString("maintain_def.json");
    QFile default_file(default_file_name);
    if ( ! default_file.copy( maintain_file_name ) ){
        qDebug() << " maintain_def.json can NOT copy as maintain.json!";
    } else {
        qDebug() << " maintain_def.json copy as maintain.json";
    }

    // 赋予目标文件权限
    if ( ! QFile::setPermissions(maintain_file_name,maintain_file_permission ) ){
        qDebug() << "Failed to set Exe-Permission -- maintain_file";
    }
    sync();
}

Maintain_Model* Dev_maintain::get_maintain_model(void)
{
    //获取发动机小时计
    double cur_hour = 30.0;//(double)m_hourmeter_info.idle_hour / 360.0;
//    m_model = new Maintain_Model();
    m_model->load_maintain_json(QString("maintain.json"),cur_hour);
    return m_model;
}

Maintain_Model* Dev_maintain::
get_maintain_config_model(void){
    m_model->load_maintain_json(QString("maintain.json"));
    return m_model;
}

int Dev_maintain::
component_maintain_confirm( const int& _index )
{
    double cur_hour =  3.0;
    //根据Json文件里面描述的小时计类型获取小时计值，用于更新最近保养时间和保养剩余时间
    QString type = m_model->get_type( _index );
    if ( type == "hm_pwron" ){
//        cur_hour = (double)m_hourmeter_info.poweron_hour/360.0;
    } else if ( type == "hm_idle" ){
//        cur_hour = (double)m_hourmeter_info.idle_hour/360.0;
    } else if ( type == "hm_work" ){
//        cur_hour = (double)m_hourmeter_info.working_hour/360.0;
    } else if ( type == "hm_move" ){
//        cur_hour = (double)m_hourmeter_info.movement_hour/360.0;
    } else if ( type == "hm_b1" ){
//        cur_hour = (double)m_hourmeter_info.B1_hour/360.0;
    } else if ( type == "hm_b2" ){
//        cur_hour = (double)m_hourmeter_info.B2_hour/360.0;
    }else {
//        Debug::log(_DEBUG_ERROR,LIGHT_RED "Component hm_type error" NONE );
        return -1;
    }
    /// 更新本模块中的模型的最近保养时间
    m_model->set_last( _index , cur_hour );

    /// 发出消息,通知hourmeter同步更新同一个元件的对应数据
//    Hours_ctrl_t hour;
//    memset( &hour,0,sizeof(Hours_ctrl_t));
//    hour.cmp_confirm[ _index / 32 ] |= ( 0x00000001 << (_index % 32) );
//    hour.command = _HOUR_CMD_CONFIRM_MAINTAIN;
//    m_shm_ctrl->set((uint8_t*)&hour,sizeof( Hours_ctrl_t));
    return 0;
}

int Dev_maintain::
component_maintain_config( const int& _index ){
    m_model->set_visible( _index );
}

int Dev_maintain::
save_all(void){
    m_model->save_maintain_file();
}


