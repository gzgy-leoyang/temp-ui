import QtQuick 2.7
import QtQuick.Controls 1.3
import QtQml 2.0

import "../../Qml_widget"

FocusScope{
    id:tgu_param_info_for_usr_fs
    width:page_root.width
    height:page_root.height

    focus: true
    x:page_root.x
    y:page_root.y
    property alias my_list: my_list

    property int page_id:1
    property string page_name: "tgu_param_info_for_usr"

    // 页面构造完成时,立即设置默认焦点组件
    Component.onCompleted: {
        listview_container.focus = true;
    }

    ListModel {
        id: list_model

        ListElement {
            type: "page"
            title: "电气故障"
            icon: ""
            right_icon:"qrc:/Pages/right_arrow_XL.png"
            view: "qrc:/Pages/History_fail/Electrical_fail/Electrical_fail.qml"
        }
        ListElement {
            type: "page"
            title: "机械故障"
            icon: ""
            right_icon:"qrc:/Pages/right_arrow_XL.png"
            view: "qrc:/Pages/History_fail/Machinery_fail/Machinery_fail.qml"
        }
        ListElement {
            type: "page"
            title: "发动机故障"
            icon: ""
            right_icon:"qrc:/Pages/right_arrow_XL.png"
            view: "qrc:/Pages/History_fail/Engine_fail/Engine_fail.qml"
        }
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
            text: "历史故障"

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

            ListView{
                id:my_list
                width: listview_container.width
                height: listview_container.height
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 5
                clip: true

                maximumFlickVelocity:5000
                keyNavigationWraps :true   //导航循环包裹list，不会到边缘就跳出
                highlightMoveDuration: 10   //设定高亮代理的移动速度，实质上是指切换动作的速度；暂时找到Value与每秒切换像素点数量的关系，value = 10效果良好。
                highlightFollowsCurrentItem: true

                model:list_model
                delegate: Mix_menu_list_item{}
                onContentYChanged: {
//                    list_scroll_bar.barY = my_list.contentY/my_list.contentHeight*list_scroll_bar.height
                }
            }
        }
    }
}

////////// end /////////////////
