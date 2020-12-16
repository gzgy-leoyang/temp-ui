#ifndef PAGE_MACHINERY_FAIL_DATA_H
#define PAGE_MACHINERY_FAIL_DATA_H

#include <QObject>
#include <string.h>
#include <QTimer>
#include <QStringList>
#include <QAbstractListModel>
#include "../dev_fail_record.h"
#include <QFile>

////////////////
class Page_machinery_fail_data : public QObject
{
    Q_OBJECT
public:
    Page_machinery_fail_data( QObject *parent = 0);
    Q_PROPERTY( Dev_fail_record* fail_data_model     READ get_fail_data_model     NOTIFY fail_data_model_changed)
    Dev_fail_record* get_fail_data_model(void) ;
signals:
    void fail_data_model_changed();
private:
    Dev_fail_record* m_fail_data_model;
};

#endif // PAGE_MACHINERY_FAIL_DATA_H
