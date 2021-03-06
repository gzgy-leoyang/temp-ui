import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQml 2.0

import "../Qml_widget"
import qml.custom.Page_maintain_set_data 1.0

FocusScope{
    id:maintain_info_set_fs
    width:page_root.width
    height:page_root.height

    focus: true
    x:page_root.x
    y:page_root.y
//    property alias my_list: my_list

    property int page_id:1
    property string page_name: "maintain_info_set"

    // 页面构造完成时,立即设置默认焦点组件
//    Component.onCompleted: {
//        listview_container.focus = true;
//        console.log("count = ", my_list.count )
//    }

    Page_maintain_set_data{id: data_src}

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
            text: "保养监控开关"

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
                delegate: Switch_listView_item{
                    onItem_clicked: {
                        console.debug("Dlg_maintain_info_item::Item_clicked.."+ my_list.currentIndex );
                        data_src.configure_component(my_list.currentIndex)
//                        data_src.confirm_component( my_list.currentIndex );
                    }
                }
                onContentYChanged: {
                }
            }
        }

    }
}

////////// end /////////////////

