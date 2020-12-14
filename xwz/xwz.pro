TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    Page_components/page_monitor_info_set_data.cpp \
    Data_components/dev_maintain.cpp \
    Page_components/page_maintain_data.cpp \
    Page_components/page_maintain_set_data.cpp \
    Pages/Setting_page/page_setting_data.cpp \
    Pages/Function_page/page_function_data.cpp \
    Pages/Initialize_setting/Machine_info/page_machine_info_data.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Page_components/page_moniter_info_set_data.h \
    Page_components/page_monitor_info_set_data.h \
    Data_components/dev_maintain.h \
    Page_components/page_maintain_data.h \
    main.h \
    Page_components/page_maintain_set_data.h \
    Pages/Setting_page/page_setting_data.h \
    Pages/Function_page/page_function_data.h \
    Pages/Initialize_setting/Machine_info/page_machine_info_data.h
