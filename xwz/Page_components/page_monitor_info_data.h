#ifndef PAGE_INFOMATION_DATA_H
#define PAGE_INFOMATION_DATA_H

#include <QObject>
#include <string.h>
#include <QTimer>
#include <QStringList>
#include <QAbstractListModel>

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


class Page_moniter_info_data : public QObject
{
    Q_OBJECT
    Q_PROPERTY( MoniterParams_Model* model  READ get_model NOTIFY model_changed)
    MoniterParams_Model* get_model(void) const { return m_model ;}

public:
    Page_moniter_info_data( QObject *parent = 0);

signals:
    void model_changed();

public slots:
    void slot_timer();

private:
    MoniterParams_Model* m_model;
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
    }Moniter_param_t;

    Moniter_param_t* m_pParams_list;

    Moniter_param_t moniter_param_list[9] = {
        {.name="发动机转速",.index= 0,
        .ratio=1,.raw=0,.max=65535,.min=0,.offset=0,
        .decimal=0,.unit="r/min",.str_list={}},

        {.name="冷却液温度",.index= 0,
        .ratio=1,.raw=0,.max=250,.min=0,.offset=0,
        .decimal=0,.unit="℃",.str_list={}},

        {.name="燃油液位",.index= 0,
        .ratio=1,.raw=0,.max=100,.min=0,.offset=0,
        .decimal=0,.unit="%",.str_list={}},

        {.name="泵比例电磁阀反馈",.index= 0,
        .ratio=1,.raw=0,.max=1000,.min=0,.offset=0,
        .decimal=0,.unit="mA",.str_list={}},

        {.name="液压油温度",.index= 0,
        .ratio=1,.raw=0,.max=210,.min=0,.offset=0,
        .decimal=0,.unit="C",.str_list={}},

        {.name="P1泵压力",.index= 0,
        .ratio=1,.raw=0,.max=1000,.min=0,.offset=0,
        .decimal=1,.unit="MPa",.str_list={}},

        {.name="P2泵压力",.index= 0,
        .ratio=1,.raw=0,.max=1000,.min=0,.offset=0,
        .decimal=1,.unit="MPa",.str_list={}},

        {.name="传感器5V电源",.index= 0,
        .ratio=1,.raw=0,.max=5,.min=0,.offset=0,
        .decimal=1,.unit="V",.str_list={}},

        {.name="允许命令锁车等级",.index= 0,
        .ratio=1,.raw=0,.max=5,.min=0,.offset=0,
        .decimal=0,.unit="",.str_list={"无GSM级别锁车", "---", "---"}},


    };
};


#endif // PAGE_INFOMATION_DATA_H
