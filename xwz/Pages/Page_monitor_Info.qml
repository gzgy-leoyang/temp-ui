import QtQuick 2.7
import QtQuick.Controls 1.3
import QtQml 2.0

import "../Qml_widget"
import qml.custom.Page_moniter_info_set_data 1.0

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

    Page_moniter_info_set_data{
        id: data_src
    }

    // 页面构造完成时,立即设置默认焦点组件
    Component.onCompleted: {
        listview_container.focus = true;
    }

    // 页面的键盘处理
//    Keys.onPressed: {
//        if (event.key === Qt.Key_Space){

//    }

    Rectangle{
        id: page_root
        width: 1280
        height: 672
        color:"#050505"
        x:0
        y:0

//        onVisibleChanged: {
//            tgu_info_data_src.shining(page_root.visible);
//        }

        /*************************  页面名称 *****************************/
        Title_row{
            id: title_row
            width: 1280
            height: 90
            anchors.bottom: listview_container.top
            anchors.bottomMargin: listview_container.border.width
            text: "监控信息"
//            KeyNavigation.up: home
//            KeyNavigation.down: listview_container
            onPicked: {
                root_stack.pop();
            }
        }
//        Rectangle{
//            id:title_row
//            height: 100
//            width: 720
//            color: "red"
//            anchors.top:parent.top
//            anchors.horizontalCenter: parent.horizontalCenter
//        }

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

//            KeyNavigation.up: title_row
//            KeyNavigation.down: home

//            onFocusChanged: {
//                if ( listview_container.focus ){
//                    border.color = global_hightlight;//  "#FF8800"
//                } else {
//                    border.color = "transparent"
//                }
//            }

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

                model:data_src.model
                delegate: Unactivable_listView_item {}
                onContentYChanged: {
//                    list_scroll_bar.barY = my_list.contentY/my_list.contentHeight*list_scroll_bar.height
                }
            }
        }

        // 触摸按键区（页底）

    }
}

////////// end /////////////////
