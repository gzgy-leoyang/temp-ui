#include "page_maintain_set_data.h"
#include "main.h"

Page_maintain_set_data::
Page_maintain_set_data(QObject *parent):QObject(parent)
{
    m_modify = 0;
    m_model = g_dev_maintain->get_maintain_config_model();
}

Page_maintain_set_data::
~Page_maintain_set_data()
{
    if ( m_modify > 0 ){
        g_dev_maintain->save_all();
    }
}

int Page_maintain_set_data::
configure_component( const int& _index )
{
    m_modify++;
    g_dev_maintain->component_maintain_config(_index );
}
