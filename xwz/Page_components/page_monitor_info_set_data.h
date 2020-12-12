#ifndef PAGE_MONITOR_INFO_SET_DATA_H
#define PAGE_MONITOR_INFO_SET_DATA_H

#include <QObject>
#include <string.h>
#include <QTimer>
#include <QStringList>
#include <QAbstractListModel>

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
    MoniterInfoSet_param(QString _name,QString _val ,QString _unit , QString _visible, QObject* parent=0);
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
    void refresh( const int& _index ,const QString& _str_val, const QString& _visible);
private:
    QList< MoniterInfoSet_param* > m_params_list;//被封装的数组
};


////////////////
class Page_moniter_info_set_data : public QObject
{
    Q_OBJECT


public:
    Page_moniter_info_set_data( QObject *parent = 0);

    Q_PROPERTY( MoniterInfoSet_Model* model  READ get_model NOTIFY model_changed)
    MoniterInfoSet_Model* get_set_model(void) const { return m_model ;}

    Q_PROPERTY( MoniterParams_Model* model  READ get_model NOTIFY model_changed)
    MoniterParams_Model* get_model(void) const { return m_model ;}

signals:
    void model_changed();

public slots:
    void slot_timer();

private:
    MoniterInfoSet_Model* m_set_model;
    MoniterParams_Model*  m_model;
    int m_sizeof_params_list;
    QTimer *timer;

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

    MoniterSet_param_t* m_pParams_list;

    MoniterSet_param_t moniter_param_list[1] = {
        {.name="发动机转速",.index= 0,
        .ratio=1,.raw=0,.max=65535,.min=0,.offset=0,
        .decimal=0,.unit="r/min",.str_list={},.visible=true}
    };
};

#endif // PAGE_MONITOR_INFO_SET_DATA_H
