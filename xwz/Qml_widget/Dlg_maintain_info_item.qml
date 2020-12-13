import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4


/*
TODO:
当使用"复合委托"时,up/down 焦点控制会有问题,目前暂时改为"单一"委托
*/

Item {
    id:root_container
    width: 1280
    height: 100

    signal headIndexChanged();
    property bool have_icon: false
    property color text_color: "#d1d4c9"
    property real font_size: 35
    property real serial_number: 0

    signal item_clicked();

    Item{
        id:text_container;
        width: 1280
        height: 100
        anchors.fill: parent;
        anchors.left: parent.left
        anchors.leftMargin: 20

        Item{
            id:name_container
            width: 600
            height: 60
//            color: "red"
            anchors.left: parent.left
//            anchors.top: parent.top
            anchors.verticalCenter: parent.verticalCenter

            Text {
                id:m_name
                text: title
                color: txt_color

                width: parent.width
                font.family: "Ubuntu"
                font.pixelSize: 35
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WrapAnywhere
            }
        }

        Item{
            id:peroid_container
            width: 240
            height: 30
//            color: "blue"
//            anchors.left: parent.left
//            anchors.top: name_container.bottom
            anchors.left: name_container.right
            anchors.verticalCenter: parent.verticalCenter

            Text {
                id:peroid_txt
                text: "周期:"+cycle+"h"
                color: txt_color

                width: parent.width
                font.family: "Ubuntu"
                font.pixelSize: 25
//                verticalAlignment: Text.AlignTop
//                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter//Text.AlignTop
                horizontalAlignment: Text.AlignLeft//Text.AlignRight
                wrapMode: Text.WrapAnywhere
            }
        }

        Item{
            id:last_time_container
            width: 240
            height: 30
//            color: "green"
//            anchors.left: peroid_container.right
            anchors.left: peroid_container.right
//            anchors.leftMargin: 0
            anchors.verticalCenter: parent.verticalCenter

//            anchors.top: name_container.bottom
            Text {
                id:last_time_txt
                text: "最近:"+last_time+"h"
                color: txt_color

                width: parent.width
                font.family: "Ubuntu"
                font.pixelSize: 25
//                verticalAlignment: Text.AlignTop
//                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter//Text.AlignTop
                horizontalAlignment: Text.AlignLeft//Text.AlignRight
                wrapMode: Text.WrapAnywhere
            }
        }

        Item{
            id:remind_container
            width: 240
            height: 30
//            color: "yellow"
//            anchors.right: parent.right
//            anchors.rightMargin: 20
            anchors.left: last_time_container.right
            anchors.leftMargin: 0
            anchors.verticalCenter: parent.verticalCenter

//            anchors.top: name_container.bottom
            Text {
                id:remind_txt
                text: "剩余:"+next_countdown+"h"
                color: txt_color

                width: parent.width
                font.family: "Ubuntu"
                font.pixelSize: 25
                verticalAlignment: Text.AlignVCenter//Text.AlignTop
                horizontalAlignment: Text.AlignLeft//Text.AlignRight
                wrapMode: Text.WrapAnywhere
            }
        }
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

    MouseArea{
        anchors.fill: parent
        onClicked: {
            my_list.focus = true;
            my_list.currentIndex = index;
            item_clicked();
        }
    }

    Keys.onPressed:{
        if (event.key === Qt.Key_Space){
            my_list.currentIndex = index;
            item_clicked();
        }
    }

    // 通过 up/down 驱动焦点转移,高亮当前持焦组件
    onFocusChanged: {
//        if ( root_container.focus ){
//            split_line.color = "#FF8800"
//        } else {
//            split_line.color = "grey"//"#050505"
//        }

        // 根据列表的内容的位置，计算当前窗口显示的第一条的索引
        // 当前位置获取的坐标,更新会慢一拍
//        maintain_info_fs = my_list.contentY / 48 ;
//        console.debug("onFocusChanged...");
//        console.debug("Y : "+my_list.contentY +" head: "+maintain_info_query_for_usr_fs.current_head_index + "Index: " +my_list.currentIndex);
        headIndexChanged();
    }
}

