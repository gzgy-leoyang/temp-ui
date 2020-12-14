#include "main.h"
#include "Page_components/page_monitor_info_set_data.h"
#include "Data_components/dev_maintain.h"
#include "Pages/Setting_page/page_setting_data.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QDebug>
#include <QTranslator>
#include <QQmlContext>

Page_moniter_info_set_data* monitor_info = NULL;
Dev_maintain*               g_dev_maintain = NULL;

void page_data_regeist(void)
{
    qmlRegisterType<Page_moniter_info_set_data>( "qml.custom.Page_moniter_info_set_data", 1, 0, "Page_moniter_info_set_data" );
    qmlRegisterType<Page_maintain_data>( "qml.custom.Page_maintain_data", 1, 0, "Page_maintain_data" );
    qmlRegisterType<Page_maintain_set_data>( "qml.custom.Page_maintain_set_data", 1, 0, "Page_maintain_set_data" );
    qmlRegisterType<Page_setting_data>( "qml.custom.Page_Setting_Data", 1, 0, "Page_Setting_Data" );

}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    monitor_info = new Page_moniter_info_set_data();
    g_dev_maintain = new Dev_maintain();
    page_data_regeist();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("moniter_info", monitor_info );

    return app.exec();
}
