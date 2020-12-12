import QtQuick 2.7
//import QtQuick.Controls 1.4
//import QtQuick.Controls.Styles 1.4

/*
TODO:
当使用"复合委托"时,up/down 焦点控制会有问题,目前暂时改为"单一"委托
*/

Item {
    id:root_container
    width: 720 - 8
    height: 1130/16
    property bool have_icon: false
    property color text_color: "#d1d4c9"
    property real font_size: 35
    anchors.horizontalCenter: parent.horizontalCenter

//    Image{
//        id:m_img;
//        width: 32;
//        height: 32;
//        anchors.left: parent.left
//        anchors.leftMargin: 2
//        y:9;
//        source: icon;
//        opacity: 1;
//        visible: have_icon
//    }

    Item{
        id:text_container;
        width:parent.width
        height: parent.height - split_line.height
        anchors.left: root_container.left
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id:m_name
            anchors.left: text_container.left
            anchors.margins: 5
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            color: text_color
            font.family: "Ubuntu"
            font.pixelSize: font_size
            text:title
        }

        Text {
            id:m_value
            text: value
            anchors.right: m_unit.left
            anchors.rightMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            color: text_color
            font.family: "Ubuntu"
            font.pixelSize: font_size
        }

        Text {
            id:m_unit
            anchors.right: text_container.right
            anchors.margins: 4
            text: unit
            anchors.rightMargin: text_container.width/20
            anchors.verticalCenter: parent.verticalCenter

            color: text_color
            font.family: "Ubuntu"
            font.pixelSize: font_size
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
//            my_list.focus = true;
            console.debug("picked index = ",index)
//            my_list.currentIndex = index;
        }
    }

    // 通过 up/down 驱动焦点转移,高亮当前持焦组件
    onFocusChanged: { }
}

