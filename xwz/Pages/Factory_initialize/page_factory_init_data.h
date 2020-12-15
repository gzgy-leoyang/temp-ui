#ifndef PAGE_FACTORY_INIT_DATA_H
#define PAGE_FACTORY_INIT_DATA_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

class Page_factory_init_data : public QObject
{
    Q_OBJECT
public:
    Page_factory_init_data(QObject *parent = 0);
    ~Page_factory_init_data();

    Q_INVOKABLE void confirm_init_clicked();
signals:
    void initialze_success();
    void initialze_failed();

private:
    int replace_file( QString _des_file_name,QString _src_file_name);
};
#endif // PAGE_FACTORY_INIT_DATA_H
