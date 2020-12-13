import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

import "./Pages"
Window {
    visible: true
    width: 1280
    height: 800

    Rectangle{
        id: root_rect_container
        anchors.fill: parent
        color: "#050505"
        Rectangle{
            id: top_info
            width: 1280
            height: 128
            color: "gray"
            Text{
                id: top_text
                text: "top"
                font.pixelSize: 50
                anchors.centerIn: parent
            }
        }
        StackView {
            id: root_stack
            height: 672
            width: 1280
            anchors.top: top_info.bottom
            focus: true
            // 初始页面
            initialItem:Page_main{}

            //  页面切换时，强制当前顶层的页面获取焦点，并标记当前页面
            onCurrentItemChanged: {
    //            currentItem.forceActiveFocus();
            }
        }
    }
}
