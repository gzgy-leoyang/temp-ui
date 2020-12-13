#include "page_maintain_data.h"
#include "main.h"

Page_maintain_data::
Page_maintain_data(QObject *parent):QObject(parent)
{
    m_modify = 0;
    m_model = g_dev_maintain->get_maintain_model();
}

Page_maintain_data::
~Page_maintain_data()
{
    if ( m_modify > 0 ){
        g_dev_maintain->save_all();
    }
}

void Page_maintain_data::
slot_timer(){}

int Page_maintain_data::
confirm_component( const int& _index )
{
    m_modify++;
    g_dev_maintain->component_maintain_confirm( _index );
}

int Page_maintain_data::
factory_initialization( void ){
    g_dev_maintain->require_factory_init();
}
