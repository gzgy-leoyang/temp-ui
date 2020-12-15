#ifndef PAGE_BOOT_MODE_DATA_H
#define PAGE_BOOT_MODE_DATA_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

class Page_boot_mode_data : public QObject
{
    Q_OBJECT
public:
    Page_boot_mode_data(QObject *parent = 0);
    ~Page_boot_mode_data();

//    void set_work_mode_booting(void);
//    int save_work_mode_shutdown( QString _file_name,int _mode );

    Q_PROPERTY( QString boot_mode  READ get_boot_mode NOTIFY boot_mode_changed )
    int get_boot_mode( void ) const {return m_boot_mode;}

    Q_INVOKABLE void p_mode_clicked();
    Q_INVOKABLE void e_mode_clicked();
    Q_INVOKABLE void last_mode_clicked();

signals:
    void boot_mode_changed(  int _mode  );
public slots:
    void slot_timer();

private:
    QTimer* m_tim;

    int m_boot_mode ;
    QString m_mode_shutdown;
    int m_modify_counter;
};
#endif // PAGE_SETTING_DATA_H
