import QtQuick 2.7
import QtQuick.Controls 1.3
import QtQml 2.0

import "../../../Qml_widget"
import qml.custom.Page_Electrical_Fail_data 1.0

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

    Page_Electrical_Fail_data{
        id:data_src
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
            width: 1280
            height: 90
            anchors.bottom: listview_container.top
            anchors.bottomMargin: listview_container.border.width
            text: "电气故障"
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

                headerPositioning:ListView.InlineHeader
                header:Rectangle{

                    height: 50
                    width: 1280
                    color:"lightgray"

                    Text {
                        id:m_name
                        text:"故障内容"
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                        anchors.verticalCenter: parent.verticalCenter
                        color: "#050505"
                        font.family: "Ubuntu"
                        font.pixelSize: 20
                    }
                    Text {
                        id:m_hour
                        text: "发生小时计"
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        anchors.verticalCenter: parent.verticalCenter
                        color: "#050505"
                        font.family: "Ubuntu"
                        font.pixelSize: 20
                    }
                }

                model:data_src.fail_data_model
//                delegate: Unactivable_listView_item {}

                delegate: Rectangle{
                    height: 100
                    width: 1280
                    color: "transparent"
                    Text {
                        id:m_name
                        text:content  /// 链接数据字段的标记

                        anchors.left: parent.left
                        anchors.leftMargin: 20
                        anchors.verticalCenter: parent.verticalCenter
                        color: "gray"
                        font.family: "Ubuntu"
                        font.pixelSize: 30
                    }
                    Text {
                        id:m_hour
                        text: hour /// 链接数据字段的标记

                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        anchors.verticalCenter: parent.verticalCenter
                        color: "gray"
                        font.family: "Ubuntu"
                        font.pixelSize: 30
                    }

                    Rectangle{
                        id:split_line
                        width: parent.width
                        height: 2
                        color: "grey"
                        opacity: 0.3
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                    }
                }
            }
        }
    }
}

////////// end /////////////////
