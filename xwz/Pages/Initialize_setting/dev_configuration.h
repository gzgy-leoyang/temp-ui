#ifndef DEV_CONFIGURATION_H
#define DEV_CONFIGURATION_H

#include <QObject>

class Dev_configuration : public QObject
{
    Q_OBJECT
public:
    explicit Dev_configuration(QObject *parent = 0);

    static int  set_key_val( QString _file_name,QString _key,QString _val );
    static int  get_key_val( QString _file_name,QString _key,QString* _val );
};

#endif // DEV_CONFIG_H
