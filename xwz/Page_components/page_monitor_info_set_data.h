#ifndef PAGE_MONITOR_INFO_SET_DATA_H
#define PAGE_MONITOR_INFO_SET_DATA_H

#include <QObject>
#include <string.h>
#include <QTimer>
#include <QStringList>
#include <QAbstractListModel>
#include <QFile>

#define _SIZEOF_PARAM_LIST (2)

/////////
class Moniter_param : public QObject
{
    Q_OBJECT
public:
    Moniter_param(QString _name,QString _val ,QString _unit ,QObject* parent=0);
    QString m_name ;
    QString m_value;
    QString m_unit;
};

class MoniterParams_Model : public QAbstractListModel
{
    Q_OBJECT
public:
    MoniterParams_Model(QObject *parent=0);

    /*必须实现的虚函数 供QML引擎调用*/
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames()  const;

    bool pushData( Moniter_param* _entry );
    void refresh( const int& _index ,const QString& _str_val );
private:
    QList< Moniter_param* > m_params_list;//被封装的数组
};
/////////
class MoniterInfoSet_param : public QObject
{
    Q_OBJECT
public:
    MoniterInfoSet_param(QString _name,QString _val ,QString _unit , bool _visible, QObject* parent=0);
    QString m_name ;
    QString m_value;
    QString m_unit;
    bool    m_visible;
};

class MoniterInfoSet_Model : public QAbstractListModel
{
    Q_OBJECT
public:
    MoniterInfoSet_Model(QObject *parent=0);

    /*必须实现的虚函数 供QML引擎调用*/
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames()  const;

    bool pushData( MoniterInfoSet_param* _entry );
    void refresh( const int& _index ,const QString& _str_val, const bool& _visible);
    bool get_visible_property( int _index );
private:
    QList< MoniterInfoSet_param* > m_params_list;//被封装的数组
};
////////////////
class Page_moniter_info_set_data : public QObject
{
    Q_OBJECT
    typedef struct {
        QString name;
        int     index;

        float   ratio;
        int     raw;
        int     max;
        int     min;
        int     offset;

        int     decimal; //小数位数
        QString unit;
        QStringList str_list;
        bool    visible; //是否显示
    }MoniterSet_param_t;
public:
    Page_moniter_info_set_data( QObject *parent = 0);

    Q_PROPERTY( MoniterInfoSet_Model* engine_set_model     READ get_engine_set_model     NOTIFY engine_set_model_changed)
    Q_PROPERTY( MoniterInfoSet_Model* hydraulic_set_model  READ get_hydraulic_set_model  NOTIFY hydraulic_set_model_changed)
    Q_PROPERTY( MoniterInfoSet_Model* electrical_set_model READ get_electrical_set_model NOTIFY electrical_set_model_changed)
    Q_PROPERTY( MoniterInfoSet_Model* config_set_model     READ get_config_set_model     NOTIFY config_set_model_changed)
    Q_PROPERTY( MoniterParams_Model*  model      READ get_model     NOTIFY model_changed)
    /// 设置页面模型，四个
    MoniterInfoSet_Model* get_engine_set_model(void) ;
    MoniterInfoSet_Model* get_hydraulic_set_model(void) ;
    MoniterInfoSet_Model* get_electrical_set_model(void) ;
    MoniterInfoSet_Model* get_config_set_model(void) ;
    MoniterParams_Model* get_model(void) ; /// 合并模型

    Q_INVOKABLE void visible_changed( int _index );
    Q_INVOKABLE void save_modify(void);
signals:
    void engine_set_model_changed();
    void hydraulic_set_model_changed();
    void electrical_set_model_changed();
    void config_set_model_changed();
    void model_changed();

public slots:
    void slot_timer();

private:
    void load_config( QString _file_name, MoniterSet_param_t* _list,int _size );
    void save_config( QString _file_name, MoniterSet_param_t* _list,int _size );

    void slot_timer_refresh_params();
    void slot_timer_refresh_set_page(MoniterSet_param_t* _param_list, MoniterInfoSet_Model* _model,int _size );

    QTimer *timer;
    int m_model_type;
    MoniterInfoSet_Model* m_current_set_model;
    MoniterSet_param_t*   m_current_set_list;
    int m_sizeof_params_list;
    MoniterSet_param_t* m_pParams_list;

    /// 全运行参数数据源与对应的model
    QList<MoniterSet_param_t*> m_all_param_list;
    MoniterParams_Model*  m_model;

    /// 各设置界面的数据源与对应的model
    MoniterInfoSet_Model* m_engine_set_model;
    MoniterInfoSet_Model* m_hydraulic_set_model;
    MoniterInfoSet_Model* m_electrical_set_model;
    MoniterInfoSet_Model* m_config_set_model;
    struct Param_set_list_t{
        ///////////
        MoniterSet_param_t moniter_param_list_engine[_SIZEOF_PARAM_LIST] = {
            {.name="发动机参数1",.index= 0,
            .ratio=1,.raw=0,.max=65535,.min=0,.offset=0,
            .decimal=0,.unit="rpm",.str_list={},.visible=true},

            {.name="发动机参数2",.index= 0,
            .ratio=1,.raw=0,.max=65535,.min=0,.offset=0,
            .decimal=0,.unit="rpm",.str_list={},.visible=true}
        };

        MoniterSet_param_t moniter_param_list_hydraulic[_SIZEOF_PARAM_LIST] = {
            {.name="液压参数1",.index= 0,
            .ratio=1,.raw=0,.max=65535,.min=0,.offset=0,
            .decimal=0,.unit="rpm",.str_list={},.visible=true},

            {.name="液压参数2",.index= 0,
            .ratio=1,.raw=0,.max=65535,.min=0,.offset=0,
            .decimal=0,.unit="rpm",.str_list={},.visible=true}
        };

        MoniterSet_param_t moniter_param_list_electrical[_SIZEOF_PARAM_LIST] = {
            {.name="电气参数1",.index= 0,
            .ratio=1,.raw=0,.max=65535,.min=0,.offset=0,
            .decimal=0,.unit="rpm",.str_list={},.visible=true},

            {.name="电气参数2",.index= 0,
            .ratio=1,.raw=0,.max=65535,.min=0,.offset=0,
            .decimal=0,.unit="rpm",.str_list={},.visible=true}
        };

        MoniterSet_param_t moniter_param_list_config[_SIZEOF_PARAM_LIST] = {
            {.name="配置参数1",.index= 0,
            .ratio=1,.raw=0,.max=65535,.min=0,.offset=0,
            .decimal=0,.unit="rpm",.str_list={},.visible=true},

            {.name="配置参数2",.index= 0,
            .ratio=1,.raw=0,.max=65535,.min=0,.offset=0,
            .decimal=0,.unit="rpm",.str_list={},.visible=true}
        };
    }Param_set_list;


};

#endif // PAGE_MONITOR_INFO_SET_DATA_H
