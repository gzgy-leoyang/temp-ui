import QtQuick 2.0

BorderImage {
    id: button
    signal clicked(string op)
    signal pressed()
    signal released()

    property alias text: buttonText.text
    property alias fontSize: buttonText.font.pixelSize
    property string op: ""
    property alias img_source : img1.source

    width: vk.width*0.08
    height: vk.height*0.21

    property real icon_h: height*0.5
    property real icon_w: width*0.5

//    source: "qrc:/icons/page_icon/VirtualKeyboard/Button.png";
    clip: true
//    border { left: 10; top: 10; right: 10; bottom: 10 }
    border { left: 0; top: 0; right: 0; bottom: 0 }
    Rectangle {
        id: shade
        anchors.fill: parent
        radius: 5
        color: "#222222";
//        border.width: 1
//        border.color: "#A9FF41"
    }
    Image {
        id : img1
        width: icon_w//0.25
        height: icon_h//0.25
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
    Text {
        id: buttonText
        anchors { centerIn: parent; }
        font.family: "Times New Roman"
        font.pixelSize: parent.width > parent.height ? parent.height * 0.7 : parent.width * 0.7
        style: Text.Sunken;
        color: "#888888"//"black";
        styleColor: "#888888";
        smooth: true
    }

    MouseArea {
        id: mouseArea
        width: 30
        anchors.fill: parent
        onClicked: button.clicked(op)
        onPressed:{
            button.pressed()
//            shade.border.color = "lightblue"
//            shade.border.width = 3;

        }
        onReleased:{
            button.released()
        }
    }

    states: State {
        name: "pressed";
        when: mouseArea.pressed === true
        PropertyChanges {
            target: shade;
//            opacity: 0.5
            color:"#111111"
        }
    }
}


