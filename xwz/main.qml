import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

import "./Pages"
Window {
    visible: true
    width: 720
    height: 1130

    Rectangle{
        id: root_rect_container
        anchors.fill: parent
        color: "#050505"
        StackView {
            id: root_stack
            anchors.fill: parent
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
