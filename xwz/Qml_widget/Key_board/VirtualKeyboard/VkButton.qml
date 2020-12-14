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

    source: "../../../images/VirtualKeyboard/Button.png";
    clip: true
    border { left: 10; top: 10; right: 10; bottom: 10 }

    Rectangle {
        id: shade
        width: 30
        anchors {
            fill: button
        }
        radius: 3
        color: "black";
        opacity: 0 //透明
    }
    Image {
        id : img1
        width: button.width * 0.25
        height: button.width * 0.25
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
    Text {
        id: buttonText
        anchors { centerIn: parent; }
        font.family: "Times New Roman"
        font.pixelSize: parent.width > parent.height ? parent.height * 0.6 : parent.width * 0.6
        style: Text.Sunken;
        color: "black";
        styleColor: "black";
        smooth: true
    }

    MouseArea {
        id: mouseArea
        width: 30
        anchors.fill: parent
        onClicked: button.clicked(op)
        onPressed: button.pressed()
        onReleased: button.released()
    }

    states: State {
        name: "pressed";
        when: mouseArea.pressed === true
        PropertyChanges {
            target: shade;
            opacity: 0.5
        }
    }
}


