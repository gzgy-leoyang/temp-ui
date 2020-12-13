import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Item {
    id: switcher_root;

    property bool   available: true
    property alias  checked_val: control.checked

    Switch {
        id: control
        checked: false

        width: 130;
        height: 50;
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter

        style: SwitchStyle {
            groove: Rectangle {
                    implicitWidth: 130
                    implicitHeight: 50
                    radius: 25
                    color:control.checked ?(available?"#505050":"#ABABAB"):(available?"#FFFFFF":"#C0C0C0")
                    border.color: "#050505"
                    border.width: 5
            }

            handle: Rectangle {
                    implicitWidth: 80
                    implicitHeight: 50
                    radius: 25
                    border.color: "#686868"
                    border.width: 5
                    color: available?"#FFFFFF":"#C0C0C0"
            }
        }
    }
}
