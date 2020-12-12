#ifndef PAGE_MONITOR_INFO_SET_DATA_H
#define PAGE_MONITOR_INFO_SET_DATA_H

#include <QObject>
#include <string.h>
#include <QTimer>
#include <QStringList>
#include <QAbstractListModel>

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

    Q_PROPERTY( MoniterInfoSet_Model* set_model  READ get_set_model NOTIFY set_model_changed)
    Q_PROPERTY( MoniterParams_Model*  model      READ get_model     NOTIFY model_changed)

    MoniterInfoSet_Model* get_set_model(void) ;
    MoniterParams_Model* get_model(void) ;

    Q_INVOKABLE void visible_changed( int _index );

signals:
    void model_changed();
    void set_model_changed();

public slots:
    void slot_timer();

private:
    int m_model_type;
    MoniterInfoSet_Model* m_set_model;
    MoniterParams_Model*  m_model;

    QTimer *timer;

    int m_sizeof_params_list;
    MoniterSet_param_t* m_pParams_list;
    MoniterSet_param_t moniter_param_list[_SIZEOF_PARAM_LIST] = {
        {.name="发动机转速",.index= 0,
        .ratio=1,.raw=0,.max=65535,.min=0,.offset=0,
        .decimal=0,.unit="rpm",.str_list={},.visible=true},

        {.name="转速2",.index= 0,
        .ratio=1,.raw=0,.max=65535,.min=0,.offset=0,
        .decimal=0,.unit="rpm",.str_list={},.visible=true}
    };
};

#endif // PAGE_MONITOR_INFO_SET_DATA_H
