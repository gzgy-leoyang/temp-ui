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
    property Item       item_focused    : null
    property int list_currentindex:0
    property bool temp_bool: false
    property int brightness: 0

    property int current_head_index: 0
    property int reposition_y: 0
    property int ddd:0

    property string value_tmp: ""
    property int i: 0
    property int len_str: 0
    property int current_view_item_num: 0
    property int current_run_mode: 0
    property int size_list: 0

    Page_moniter_info_set_data{
        id: data_src
    }

    // 页面构造完成时,立即设置默认焦点组件
    Component.onCompleted: {
        listview_container.focus = true;
    }

    Rectangle{
        id: page_root
        width: 720
        height: 1130
        color:"#050505"
        x:0
        y:0

//        onVisibleChanged: {
//            data_src.shining(page_root.visible);
//        }

        /*************************  页面名称 *****************************/
        Title_row{
            id: title_row
            anchors.bottom: listview_container.top
            anchors.bottomMargin: listview_container.border.width
            text: "监控信息设置"

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

                model:data_src.model
                delegate: Switch_listView_item{}
                onContentYChanged: {
//                    list_scroll_bar.barY = my_list.contentY/my_list.contentHeight*list_scroll_bar.height
                }
            }
        }
    }
}

////////// end /////////////////
