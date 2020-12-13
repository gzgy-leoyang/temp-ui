
#include "Page_components/page_monitor_info_set_data.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QDebug>
#include <QTranslator>
#include <QQmlContext>


Page_moniter_info_set_data* monitor_info = NULL;

void page_data_regeist(void)
{
    qmlRegisterType<Page_moniter_info_set_data>( "qml.custom.Page_moniter_info_set_data", 1, 0, "Page_moniter_info_set_data" );
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    monitor_info = new Page_moniter_info_set_data();

    page_data_regeist();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("moniter_info", monitor_info );

    return app.exec();
}
