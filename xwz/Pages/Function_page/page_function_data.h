#ifndef PAGE_FUNCTION_DATA_H
#define PAGE_FUNCTION_DATA_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

class Page_function_data : public QObject
{
    Q_OBJECT
public:
    Page_function_data(QObject *parent = 0);
    ~Page_function_data();

    Q_PROPERTY( QString auto_lock  READ get_auto_lock NOTIFY auto_lock_changed )
    QString get_auto_lock( void ) const;

    Q_PROPERTY( QString cmd_lock  READ get_cmd_lock NOTIFY cmd_lock_changed )
    QString get_cmd_lock( void ) const;

    Q_INVOKABLE void auto_lock_clicked();
    Q_INVOKABLE void cmd_lock_clicked();

signals:
    void auto_lock_changed( QString _lock );
    void cmd_lock_changed( QString _lock );
public slots:
    void slot_timer();

private:
    int set_auto_lock_cmd( const int& _val );
    int set_cmd_lock_cmd( const int& _val );
    int m_auto_lock ;
    int m_cmd_lock ;

    QTimer* m_timer;
};
#endif // PAGE_SETTING_DATA_H
