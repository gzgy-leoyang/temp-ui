import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: dlg_root
    width: 720
    height: 100
    color: "transparent"
    border.width: 4
    border.color: "transparent"
    anchors.horizontalCenter: parent.horizontalCenter

    property color text_color: "white"
    property real font_size: 35

    property var cmp_obj: null
    property var page_obj: null

    property real line_width: 0
    property real line_x: 0

    signal item_clicked();
    signal item_switch_checked();

    /////////////////

    Rectangle{
        id: type_switch_container
        width:dlg_root.width
        height: dlg_root.height
        color: "transparent"
        border.width: 4
        border.color: "transparent"

        Text {
            id:m_name
            text:title
            width: 300
            anchors.left: parent.left
            anchors.leftMargin: 20;
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            color: text_color
            font.family: "Ubuntu"
            font.pixelSize: font_size
        }

        Text {
            id:m_value
            text: value
            anchors.left: m_name.right
            anchors.verticalCenter: parent.verticalCenter
            color: text_color
            font.family: "Ubuntu"
            font.pixelSize: font_size
        }

        Text {
            id:m_unit
            anchors.left: m_value.right
            anchors.margins: 4
            text: unit
            anchors.verticalCenter: parent.verticalCenter

            color: text_color
            font.family: "Ubuntu"
            font.pixelSize: font_size
        }

        //            Switcher{
        //                id: control
        //                available: true;
        //                checked_val: (value==="1")?true:false;

        //                anchors.right: parent.right
        //                anchors.rightMargin: 20
        //                anchors.verticalCenter: parent.verticalCenter
        //            }

        Item {
            id: switcher_root;
            width: 130;
            height: 50;
            property bool   available: true
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter

            Switch {
                id: control
//                checked: (display==="1")?true:false;
                width: 130;
                height: 50;
                anchors.centerIn: parent

                style: SwitchStyle {
                    groove: Rectangle {
                        implicitWidth: 130
                        implicitHeight: 50
                        radius: 25
                        color:control.checked ?(switcher_root.available?"#505050":"#ABABAB"):(switcher_root.available?"#FFFFFF":"#C0C0C0")
                        border.color: "#050505"
                        border.width: 5
                    }

                    handle: Rectangle {
                        implicitWidth: 80
                        implicitHeight: 50
                        radius: 25
                        border.color: "#686868"
                        border.width: 5
                        color: switcher_root.available?"#FFFFFF":"#C0C0C0"
                    }
                }

                onCheckedChanged: {
                    console.log("checked")
                }
            }
        }

        Rectangle{
            id: line
            height: 1
            anchors.left: m_name.left
            anchors.right: switcher_root.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            color: "grey"
            opacity: 0.5
            Component.onCompleted: {
                line_width = width
                line_x = x
            }
        }
    }


    onFocusChanged: {
    }

    MouseArea{
        anchors.fill: parent;
        onClicked: {
            my_list.focus = true;
            my_list.currentIndex = index;
            item_clicked();
//            console.log("index = ", index)
        }
    }
}

