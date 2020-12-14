#ifndef PAGE_SETTING_DATA_H
#define PAGE_SETTING_DATA_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

class Page_setting_data : public QObject
{
    Q_OBJECT
public:
    Page_setting_data(QObject *parent = 0);
    ~Page_setting_data();

    Q_PROPERTY( QString idle_delay  READ get_idle_delay WRITE set_idle_delay NOTIFY idle_delay_changed )
    QString get_idle_delay( void ) const;
    void set_idle_delay( QString phone_num );

    Q_PROPERTY( QString coolant_comp  READ get_coolant_comp WRITE set_coolant_comp NOTIFY coolant_comp_changed )
    QString get_coolant_comp( void ) const;
    void set_coolant_comp( QString phone_num );

    Q_PROPERTY( QString hydraulic_comp  READ get_hydraulic_comp WRITE set_hydraulic_comp NOTIFY hydraulic_comp_changed )
    QString get_hydraulic_comp( void ) const;
    void set_hydraulic_comp( QString phone_num );

signals:
    void idle_delay_changed( QString _phone_num );
    void coolant_comp_changed( QString _coolant_comp );
    void hydraulic_comp_changed( QString _hydraulic_comp );
public slots:

private:
    int set_idle_delay_cmd( const int& _val );
    int set_coolant_comp_cmd( const int& _val );
    int set_hydraulic_comp_cmd( const int& _val );

    int load_config(const QString& fileName);
    int save_config(QString fileName);

    int m_idle_delay ;
    int m_coolant_comp;
    int m_hydraulic_comp;

    int m_modify_counter;
};
#endif // PAGE_SETTING_DATA_H
