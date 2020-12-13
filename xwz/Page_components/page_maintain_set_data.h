#ifndef PAGE_MAINTAIN_SET_DATA_H
#define PAGE_MAINTAIN_SET_DATA_H

#include "Data_components/dev_maintain.h"
#include <QObject>
#include <QList>
#include <QAbstractListModel>
#include <QVariant>

class Page_maintain_set_data : public QObject
{
    Q_OBJECT
public:
    Page_maintain_set_data(QObject *parent = 0);
    ~Page_maintain_set_data();

    Q_PROPERTY(Maintain_Model* model  READ get_model NOTIFY model_changed)
    Maintain_Model* get_model(void) { return m_model ;}

    Q_INVOKABLE int configure_component( const int& _index );

signals:
    void model_changed();

private:
    Maintain_Model* m_model;
    int m_modify;
};

#endif // PAGE_MAINTAIN_SET_DATA_H
