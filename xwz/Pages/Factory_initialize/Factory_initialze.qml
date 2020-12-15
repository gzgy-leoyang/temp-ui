import QtQuick 2.7
import QtQuick.Controls 1.3
import QtQml 2.0

import "../../Qml_widget"
import qml.custom.Page_Factory_Init_Data 1.0

FocusScope{
    id:tgu_param_info_for_usr_fs
    width:page_root.width
    height:page_root.height

    focus: true
    x:page_root.x
    y:page_root.y

    property int page_id:1
    property string page_name: "initialize_setting"


    Page_Factory_Init_Data{
        id: data_src
    }

    // 页面构造完成时,立即设置默认焦点组件
    Component.onCompleted: {
        listview_container.focus = true;
    }

    Rectangle{
        id: page_root
        width: 1280
        height: 672
        color:"#050505"
        x:0
        y:0

        /*************************  页面名称 *****************************/
        Title_row{
            id: title_row
            anchors.bottom: listview_container.top
            anchors.bottomMargin: listview_container.border.width
            text: "出厂初始化"

            onPicked: {
                root_stack.pop();
            }
        }

        Rectangle{
            id:listview_container
            width: page_root.width
            height: page_root.height - (   title_row.height)
            color:"#050505"
            border.width: 4;
            border.color: "#050505"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            clip: true


        }

        Button {
            width: 100
            height: 80

            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: "确认"
            onClicked: {
                data_src.confirm_init_clicked();
            }
        }
    }
}

////////// end /////////////////
