import QtQuick 2.7

Rectangle{
    id: title_root
    height: 90
    width: 1280
    property real font_size: 35
    property alias text: title_text.text
    property color text_color: "white"
    border.width: 4
    border.color: "transparent"
    color: "transparent"

    signal picked();

//    onFocusChanged: {
//        if(title_root.focus){
//            title_root.border.color = "";
//        }
//        else{
//            title_root.border.color = "transparent";
//        }
//    }

    Row{
        height: parent.height-2
        width: parent.width
        spacing: parent.width/20
        leftPadding: parent.width/25
        Rectangle{
            height: title_root.height-2
            width: title_root.width*0.056
            color: "transparent"
            Image {
                id: back_icon
                width: parent.width
                height: parent.height*0.5
                anchors.centerIn: parent
                source: "qrc:/Qml_widget/left.png"
            }
        }

        Item{
            height: title_root.height-2
            width: 30
            Text {
                id: title_text

                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("text")
                font.pixelSize: font_size
                color: text_color
            }
        }

    }

    Rectangle{
        id: line
        width: parent.width
        height: 2
        color: text_color
        anchors.bottom: parent.bottom
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            picked();
        }
    }
}
