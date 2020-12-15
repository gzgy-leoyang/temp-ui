#ifndef PAGE_UNIT_SET_DATA_H
#define PAGE_UNIT_SET_DATA_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

class Page_unit_set_data : public QObject
{
    Q_OBJECT
public:
    Page_unit_set_data(QObject *parent = 0);
    ~Page_unit_set_data();

    Q_PROPERTY( QString units  READ get_units NOTIFY units_changed )
    int get_units( void ) const {return m_units;}

    Q_INVOKABLE void si_units_clicked();
    Q_INVOKABLE void metric_units_clicked();
    Q_INVOKABLE void imperial_units_clicked();

signals:
    void units_changed(  int _units  );
public slots:
    void slot_timer();

private:
    QTimer* m_tim;
    int m_units ;
    int m_modify_counter;
};
#endif // PAGE_UNIT_SET_DATA_H
