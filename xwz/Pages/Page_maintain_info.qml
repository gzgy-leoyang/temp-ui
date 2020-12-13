import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQml 2.0

import "../Qml_widget"

import qml.custom.Page_maintain_data 1.0

FocusScope{
    id:maintain_info_fs
    width:page_root.width
    height:page_root.height

    focus: true
    x:page_root.x
    y:page_root.y
    //    property alias my_list: my_list

    property int page_id:1
    property string page_name: "maintain_info"

    // 页面构造完成时,立即设置默认焦点组件
    Component.onCompleted: {
        //        listview_container.focus = true;
        console.log("count = ", my_list.count )
    }

    Page_maintain_data{id: data_src}

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
            text: "保养记录"

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
                height: listview_container.height - 80
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 5
                clip: true

                maximumFlickVelocity:5000
                keyNavigationWraps :true   //导航循环包裹list，不会到边缘就跳出
                highlightMoveDuration: 10   //设定高亮代理的移动速度，实质上是指切换动作的速度；暂时找到Value与每秒切换像素点数量的关系，value = 10效果良好。
                highlightFollowsCurrentItem: true

                model:data_src.model
                delegate: Dlg_maintain_info_item{
                    onItem_clicked: {
                        console.debug("Dlg_maintain_info_item::Item_clicked.."+ my_list.currentIndex );
                        data_src.confirm_component( my_list.currentIndex );
                    }
                }
                onContentYChanged: {
                    //                    list_scroll_bar.barY = my_list.contentY/my_list.contentHeight*list_scroll_bar.height
                }
            }
        }

        Button {
            width: 100
            height: 80
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            text: "恢复默认周期"
            onClicked: {
                tips_container.visible = true
            }
        }
    }

    Rectangle{
        id: overlay
        anchors.fill: parent
        color: "#050505"
        opacity: 0.9
        visible: tips_container.visible
        MouseArea{
            anchors.fill: parent
            onClicked: {
            }
        }
    }
    Rectangle{
        id: tips_container
        width: 500
        height: 300
        color: "#050505"
        border.width: 3
        border.color: "#AAAAAA"
        anchors.centerIn: parent
        visible: false
        Text {
            id:tips
            text: qsTr("确认恢复默认周期?")
            color: "white"
            font.pixelSize: 30
            anchors.centerIn: parent
        }
        Button {
            id: sure_btn
            width: 80
            height: 60
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 200
            text: "确定"
            onClicked: {
                data_src.factory_initialization();
            }
        }

        Button {
            id: cancel_btn
            width: 80
            height: 60
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -200
            text: "取消"
            onClicked: {
                tips_container.visible = false
            }

        }
    }
}

////////// end /////////////////

