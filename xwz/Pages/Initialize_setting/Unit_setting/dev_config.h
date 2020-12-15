#ifndef DEV_CONFIG_H
#define DEV_CONFIG_H

#include <QObject>

class Dev_config : public QObject
{
    Q_OBJECT
public:
    explicit Dev_config(QObject *parent = 0);

    int  load_config(const QString& fileName);
    void set_work_mode_booting(void);
    int  save_boot_mode( QString fileName,int _boot_mode );
    int  save_work_mode_shutdown( QString _file_name,int _mode );

    int     m_boot_mode ;
    QString m_mode_shutdown;
signals:

public slots:

private:
    int set_boot_mode_cmd( const int& _val );
};

#endif // DEV_CONFIG_H
