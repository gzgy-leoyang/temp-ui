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
        width: 1280
        height: 800
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
        }
    }

}


