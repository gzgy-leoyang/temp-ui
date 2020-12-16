#ifndef PAGE_DELETE_RECORD_DATA_H
#define PAGE_DELETE_RECORD_DATA_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

class Page_delete_record_data : public QObject
{
    Q_OBJECT
public:
    Page_delete_record_data(QObject *parent = 0);
    ~Page_delete_record_data();

    Q_INVOKABLE void confirm_delete_clicked();
signals:
    void delete_success();
    void delete_failed();

private:
    int replace_file( QString _des_file_name,QString _src_file_name);
};
#endif // PAGE_DELETE_RECORD_DATA_H