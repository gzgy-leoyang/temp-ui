#ifndef DEV_MAINTAIN_H
#define DEV_MAINTAIN_H
#include <QObject>
#include <QList>
#include <QAbstractListModel>
#include <QVariant>
#include <QFile>
#include <QColor>

///Data
class Component_entry : public QObject
{
    Q_OBJECT
public:
    Component_entry(QString _name,int _peroid,double _last,QString _type,QObject* parent=0);
    Component_entry(QString _name,int _peroid,int _last,QString _type,bool _visible,QString _date,QObject* parent=0);
    QString m_name ;
    QString m_type;
    int m_peroid;
    double m_last;
    double m_next;
    double m_remaind;
    QColor m_color;
    bool   m_visible;
    QString m_last_date;
};

///model
class Maintain_Model : public QAbstractListModel
{
    Q_OBJECT
public:
    Maintain_Model(QObject *parent=0);
    void load_maintain_json( QString _file_name );                        //不显示详细信息(例如：周期、剩余时间)
    void load_maintain_json(QString _file_name,const double& _cur_hour ); //传入小时计，显示详细信息

    /*必须实现的虚函数 供QML引擎调用*/
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames()  const override;

    bool pushData( Component_entry* _entry );
    void set_last( const int& _index ,const double& _val ) ;
    void set_visible( const int& _index );
    int save_maintain_file(void);

    QString get_type( const int& _index ) const { return m_component_list.at(_index)->m_type ;}

    double m_current_hour;
private:
    QList< Component_entry* > m_component_list;
};


class Dev_maintain : public QObject
{
    Q_OBJECT
public:
    explicit Dev_maintain(QObject *parent = 0);
    int component_maintain_confirm( const int& _index );
    int component_maintain_config( const int& _index );
    int save_all(void);
    int require_factory_init();

    Maintain_Model* get_maintain_model(void) ;//{ return m_model; }
    Maintain_Model* get_maintain_config_model(void);
    int m_maintain_reminder[4];

private:
    Maintain_Model* m_model;
};


#endif // DEV_MAINTAIN_H
