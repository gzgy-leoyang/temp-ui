import QtQuick 2.7
import QtQuick.Controls 1.4

FocusScope{
    id:main_view_fs
    width:page_root.width
    height:page_root.height
    focus:true
    x:page_root.x
    y:page_root.y
    Rectangle{
        id:page_root
        width: 720
        height: 1130
        color: "#050505"
        //按键
        Row{
            height: 100
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Button {
                width: 100
                height: 80
                text: "监控信息"
                onClicked: {
                    var cmp = Qt.createComponent( "qrc:/Pages/Page_monitor_Info.qml" );
                    var page = cmp.createObject(root_rect_container,{});
                    root_stack.push({item:page, destroyOnPop:true});
                }
            }

            Button {
                width: 100
                height: 80
                text: "监控信息设置"
                onClicked: {
                    var cmp = Qt.createComponent( "qrc:/Pages/Page_monitor_info_set.qml" );
                    var page = cmp.createObject(root_rect_container,{});
                    root_stack.push({item:page, destroyOnPop:true});
                }
            }

            Button {
                width: 100
                height: 80
                text: "保养记录"
                onClicked: {
                    var cmp = Qt.createComponent( "qrc:/Pages/Page_maintain_info.qml" );
                    var page = cmp.createObject(root_rect_container,{});
                    root_stack.push({item:page, destroyOnPop:true});
                }
            }

            Button {
                width: 100
                height: 80
                text: "保养监控开关"
                onClicked: {
                    var cmp = Qt.createComponent( "qrc:/Pages/Page_maintain_info_set.qml" );
                    var page = cmp.createObject(root_rect_container,{});
                    root_stack.push({item:page, destroyOnPop:true});
                }
            }

            Button {
                width: 100
                height: 80
                text: "参数设定"
                onClicked: {
                    var cmp = Qt.createComponent( "qrc:/Pages/Setting_page/Setting.qml" );
                    var page = cmp.createObject(root_rect_container,{});
                    root_stack.push({item:page, destroyOnPop:true});
                }
            }

            Button {
                width: 100
                height: 80
                text: "功能设置"
                onClicked: {
                    var cmp = Qt.createComponent( "qrc:/Pages/Function_page/Function.qml" );
                    var page = cmp.createObject(root_rect_container,{});
                    root_stack.push({item:page, destroyOnPop:true});
                }
            }

            Button {
                width: 100
                height: 80
                text: "初始化设置"
                onClicked: {
                    var cmp = Qt.createComponent( "qrc:/Pages/Initialize_setting/Page_Initialize_set.qml" );
                    var page = cmp.createObject(root_rect_container,{});
                    root_stack.push({item:page, destroyOnPop:true});
                }
            }

            Button {
                width: 100
                height: 80
                text: "出厂初始化"
                onClicked: {
                    var cmp = Qt.createComponent( "qrc:/Pages/Factory_initialize/Factory_initialze.qml" );
                    var page = cmp.createObject(root_rect_container,{});
                    root_stack.push({item:page, destroyOnPop:true});
                }
            }

            Button {
                width: 100
                height: 80
                text: "历史故障"
                onClicked: {
                    var cmp = Qt.createComponent( "qrc:/Pages/History_fail/History_fail.qml" );
                    var page = cmp.createObject(root_rect_container,{});
                    root_stack.push({item:page, destroyOnPop:true});
                }
            }

            Button {
                width: 100
                height: 80
                text: "删除历史故障"
                onClicked: {
                    var cmp = Qt.createComponent( "qrc:/Pages/Delete_fail_record/Delete_record.qml" );
                    var page = cmp.createObject(root_rect_container,{});
                    root_stack.push({item:page, destroyOnPop:true});
                }
            }
        }
    }
}


