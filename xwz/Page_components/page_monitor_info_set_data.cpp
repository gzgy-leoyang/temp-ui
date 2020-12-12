#include "page_monitor_info_set_data.h"
#include <QDebug>


/// >>> 数据
Moniter_param::
Moniter_param(QString _name,QString _val ,QString _unit ,QObject* parent):
    QObject(parent),
    m_name(_name),
    m_value(_val),
    m_unit(_unit)
{
}
/// <<< 数据

/// >>> 模型
MoniterParams_Model::
MoniterParams_Model(QObject *parent):
    QAbstractListModel(parent)
{
    qDebug() << "MoniterParams_Model:: MoniterParams_Model";
}

int MoniterParams_Model::
rowCount(const QModelIndex &parent) const
{
    return m_params_list.count();//返回私有列表数据量
}

QVariant MoniterParams_Model::
data(const QModelIndex &index, int role) const
{
    Moniter_param* tt = m_params_list.at(index.row());
    if (role == Qt::UserRole){
        return tt->m_name;
    }

    if (role == Qt::UserRole+1){
        return tt->m_value;
    }

    if (role == Qt::UserRole+2){
        return tt->m_unit;
    }
}

QHash<int, QByteArray> MoniterParams_Model::
roleNames() const
{
    QHash<int, QByteArray>  hash;
    hash.insert(Qt::UserRole,      QByteArray("title"));
    hash.insert(Qt::UserRole+1,      QByteArray("value"));
    hash.insert(Qt::UserRole+2,      QByteArray("unit"));
    return hash;
}

bool MoniterParams_Model::
pushData(Moniter_param* _entry)
{
    if ( _entry == NULL ){
        return false;
    }

    if ( &m_params_list == NULL ){
        return false;
    }
    beginInsertRows( QModelIndex(), m_params_list.count(), m_params_list.count());
    m_params_list.append(_entry);
    endInsertRows();
    return true;
}

void MoniterParams_Model::
refresh( const int& _index ,const QString& _str_val )
{
    Moniter_param* tt = m_params_list.at(_index);
    QModelIndex indexxx = index(_index);
    tt->m_value = _str_val;
    emit QAbstractItemModel::dataChanged(indexxx,indexxx);
}

/// <<< 模型
/////////////////

/// >>> 数据
MoniterInfoSet_param::
MoniterInfoSet_param(QString _name,QString _val ,QString _unit , bool _visible, QObject* parent):
    QObject(parent),
    m_name(_name),
    m_value(_val),
    m_unit(_unit),
    m_visible(_visible)
{
}
/// <<< 数据

/// >>> 模型
MoniterInfoSet_Model::
MoniterInfoSet_Model(QObject *parent):
    QAbstractListModel(parent)
{
}

int MoniterInfoSet_Model::
rowCount(const QModelIndex &parent) const
{
    return m_params_list.count();//返回私有列表数据量
}

QVariant MoniterInfoSet_Model::
data(const QModelIndex &index, int role) const
{
    MoniterInfoSet_param* tt = m_params_list.at(index.row());
    if (role == Qt::UserRole){
        return tt->m_name;
    }

    if (role == Qt::UserRole+1){
        return tt->m_value;
    }

    if (role == Qt::UserRole+2){
        return tt->m_unit;
    }

    if (role == Qt::UserRole+3){
        return tt->m_visible;
    }
}

QHash<int, QByteArray> MoniterInfoSet_Model::
roleNames() const
{
    QHash<int, QByteArray>  hash;
    hash.insert(Qt::UserRole,      QByteArray("title"));
    hash.insert(Qt::UserRole+1,      QByteArray("value"));
    hash.insert(Qt::UserRole+2,      QByteArray("unit"));
    hash.insert(Qt::UserRole+3,      QByteArray("display"));
    return hash;
}

bool MoniterInfoSet_Model::
pushData(MoniterInfoSet_param* _entry)
{
    if ( _entry == NULL ){
        return false;
    }

    if ( &m_params_list == NULL ){
        return false;
    }
    beginInsertRows( QModelIndex(), m_params_list.count(), m_params_list.count());
    m_params_list.append(_entry);
    endInsertRows();
    return true;
}

void MoniterInfoSet_Model::
refresh( const int& _index ,const QString& _str_val, const bool& _visible )
{
    MoniterInfoSet_param* tt = m_params_list.at(_index);
    QModelIndex indexxx = index(_index);
    tt->m_value = _str_val;
    tt->m_visible = _visible;
    emit QAbstractItemModel::dataChanged(indexxx,indexxx);
}

/// <<< 模型
/////////////////
Page_moniter_info_set_data::
Page_moniter_info_set_data(QObject *parent):
    QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_timer()));
    timer->start(500);

    m_model_type = 0 ;
}

void Page_moniter_info_set_data::
visible_changed( int _index )
{
    if ( _index >= m_sizeof_params_list ){
        return ;
    }

    MoniterSet_param_t* pParams = &moniter_param_list[_index];
    qDebug()<<"@pParams"<<pParams;

    if ( pParams->visible == true ){
        pParams->visible = false;
    } else {
        pParams->visible = true;
    }
    qDebug()<<"pParams->visible"<<_index<<pParams->visible;
}

MoniterInfoSet_Model* Page_moniter_info_set_data::
get_set_model(void)
{
    m_model_type = 1 ;

    m_set_model = new MoniterInfoSet_Model(this);
    m_pParams_list = moniter_param_list;
    m_sizeof_params_list = _SIZEOF_PARAM_LIST;

    for ( int i=0; i<m_sizeof_params_list; i++ ){
        MoniterSet_param_t t = *(m_pParams_list+i);
        MoniterInfoSet_param* tt = new MoniterInfoSet_param(t.name,"...",t.unit,t.visible,this);
        m_set_model->pushData(tt);
    }

    return m_set_model ;
}

MoniterParams_Model* Page_moniter_info_set_data::
get_model(void)
{
    m_model_type = 0 ;

    m_model = new MoniterParams_Model(this);
    m_pParams_list = moniter_param_list;
    m_sizeof_params_list = _SIZEOF_PARAM_LIST;

    for ( int i=0; i<m_sizeof_params_list; i++ ){
        MoniterSet_param_t t = *(m_pParams_list+i);

        qDebug()<<"@t"<<&t;
        qDebug()<<"t->visible"<<i<<t.visible;

        if ( t.visible == true ){
            Moniter_param* tt = new Moniter_param(t.name,"...",t.unit,this);
            m_model->pushData(tt);
        }
    }

    return m_model ;
}


void Page_moniter_info_set_data::
slot_timer()
{
    for ( int i=0;i<m_sizeof_params_list;i++ ){
        MoniterSet_param_t t = *(m_pParams_list+i);

        uint32_t temp = 0;//g_can_data->get( t.index );
        if ( temp > t.max ){
            temp = t.max;
        } else if( temp < t.min ){
            temp = t.min;
        }

        QString val_str;
        if ( t.str_list.isEmpty() ){
            double db_temp = ((temp * t.ratio) - t.offset);
            val_str = QString::number( db_temp,'f',t.decimal);
        } else {
            if ( temp >= t.str_list.count() ){
                val_str = "--";
            } else {
                val_str = t.str_list[temp];
            }
        }

        if ( m_model_type == 0 ){
            m_model->refresh(i,val_str);
        } else if ( m_model_type == 1 ){
            m_set_model->refresh(i,val_str,t.visible);
        }
    }
}



