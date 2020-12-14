#ifndef PAGE_MACHINE_INFO_DATA_H
#define PAGE_MACHINE_INFO_DATA_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

class Page_machine_info_data : public QObject
{
    Q_OBJECT
public:
    Page_machine_info_data(QObject *parent = 0);
    ~Page_machine_info_data();

    Q_PROPERTY( QString machine_model  READ get_machine_model WRITE set_machine_model NOTIFY machine_model_changed )
    QString get_machine_model( void ) const;
    void set_machine_model( QString _model );

    Q_PROPERTY( QString machine_sn  READ get_machine_sn WRITE set_machine_sn NOTIFY machine_sn_changed )
    QString get_machine_sn( void ) const;
    void set_machine_sn( QString _sn );

signals:
    void machine_model_changed( QString _model );
    void machine_sn_changed( QString _sn );
public slots:

private:

    int load_config(const QString& fileName);
    int save_config(QString fileName);

    QString m_machine_model ;
    QString m_machine_sn;

    int m_modify_counter;
};
#endif // PAGE_SETTING_DATA_H
