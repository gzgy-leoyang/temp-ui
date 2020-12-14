import QtQuick 2.4

Rectangle {
    id: vk

    width: (keyBoardStyle == 2)?vkcWidth_mini:vkcWidth
    height: vkcHeight
    color: "transparent"//"#5f5252"
    radius: 1
//    opacity: 0.2
    clip: true
    border.width: 0
    border.color: "#333333"//"#5f5252"
    state: parent.activeFocus ? "active" : "inactive"
    property Item surface: parent
    signal buttonPressed(string op)

    //键盘配置选项
    property bool capsLock:     false   //大小写
    property int keyBoardStyle: 0       //按鍵类型 2为mini键盘  1为数字  0为字母
    property int vkcWidth:    vk.width  //1024    //键盘宽度
    property int vkcWidth_mini: 200//400     //mini数字键盘宽度
    property int vkcHeight:     vk.height//280     //键盘高度
    property int y_size:        0       //键盘y轴移动位置 (2020.06.03 add)

    //字母全键盘
    Column {
        visible: (keyBoardStyle===0)?true:false
        id: vkc
        anchors.topMargin: 5
        anchors.fill: parent
        spacing: vk.height/30
        Row {
            x: vk.width/100
            spacing: vk.width/100
           VkButton { text: capsLock?"q":"Q"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"w":"W"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"e":"E"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"r":"R"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"t":"T"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"y":"Y"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"u":"U"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"i":"I"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"o":"O"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"p":"P"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {
               width: vk.width/10.24;icon_h:vk.height*0.12;icon_w: vk.width*0.06;
               img_source:"VirtualKeyboard/backspace.png";
               op: "dle";Component.onCompleted:clicked.connect(buttonPressed)}
//           VkButton { width: vk.width/10.24;icon_h:vk.height*0.12;icon_w: vk.width*0.06;img_source:"qrc:/icons/page_icon/VirtualKeyboard/backspace.png";op: "dle";Component.onCompleted:clicked.connect(buttonPressed)}
        }
        Row {
            x: vk.width/20
            spacing: vk.width/100
           VkButton { text: capsLock?"a":"A"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"s":"S"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"d":"D"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"f":"F"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"g":"G"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"h":"H"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"j":"J"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"k":"K"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"l":"L"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {width: vk.width/10.24;op: "Back";
               img_source: "VirtualKeyboard/delete.png";
               Component.onCompleted:clicked.connect(buttonPressed)}

//           VkButton {width: vk.width/10.24;op: "Back";img_source: "qrc:/icons/page_icon/VirtualKeyboard/delete.png"; Component.onCompleted:clicked.connect(buttonPressed)}
        }
        Row {
            x: vk.width/100
            spacing: vk.width/100
            VkButton {
                fontSize: 50*0.3;
                width: vk.width/12
                img_source:"VirtualKeyboard/Shift.png"
//                img_source:"qrc:/icons/page_icon/VirtualKeyboard/Shift.png"//"qrc:/icons/page_icon/VirtualKeyboard/CaseSw.png";
                onClicked: {
                    if(capsLock === true)
                    {
                        capsLock = false
                    }
                    else
                    {
                        capsLock = true
                    }
                }
            }
           VkButton { text: capsLock?"z":"Z"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"x":"X"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"c":"C"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"v":"V"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"b":"B"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"n":"N"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"m":"M"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?",":","; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?".":"."; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { text: capsLock?"'":"'"; op: text; Component.onCompleted: clicked.connect(buttonPressed)}
        }
        Row {
            x: vk.width/75
            spacing: vk.width/100
            VkButton {
                width: vk.width/9.31
                fontSize: vk.width/30
                text: ".?123"
                Component.onCompleted:
                    clicked.connect(buttonPressed)
                onClicked: {
                    keyBoardStyle = 1
                }
            }
           VkButton {fontSize: vk.width/25;text: "@"; op: text; Component.onCompleted: clicked.connect(buttonPressed) }
           VkButton {width: vk.width/1.83;icon_h:vk.height*0.17;icon_w: vk.width*0.08;
               img_source:"VirtualKeyboard/space.png";
               op: " ";Component.onCompleted:clicked.connect(buttonPressed)}

//           VkButton {width: vk.width/1.83;icon_h:vk.height*0.17;icon_w: vk.width*0.08; img_source:"qrc:/icons/page_icon/VirtualKeyboard/space.png";op: " ";Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width/14.63;text: "-";op: text;Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width/7.88;
               img_source:"VirtualKeyboard/enter.png";
               op: "Enter";Component.onCompleted:clicked.connect(buttonPressed)}

//           VkButton {width: vk.width/7.88;img_source:"qrc:/icons/page_icon/VirtualKeyboard/enter.png";op: "Enter";Component.onCompleted:clicked.connect(buttonPressed)}
        }
    }

    //数字字符
    Column {
        visible: (keyBoardStyle===1)?true:false
        id: vkcNum
        anchors.topMargin: 5
        anchors.fill: parent
        spacing: vk.height/30
        Row {
            x: vk.width/100
            spacing: vk.width/100
           VkButton { fontSize: vk.width/15;text: "1"; op: "1"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { fontSize: vk.width/15;text: "2"; op: "2"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { fontSize: vk.width/15;text: "3"; op: "3"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { fontSize: vk.width/15;text: "4"; op: "4"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { fontSize: vk.width/15;text: "5"; op: "5"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { fontSize: vk.width/15;text: "6"; op: "6"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { fontSize: vk.width/15;text: "7"; op: "7"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { fontSize: vk.width/15;text: "8"; op: "8"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { fontSize: vk.width/15;text: "9"; op: "9"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton { fontSize: vk.width/15;text: "0"; op: "0"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {width: vk.width/10.24;icon_h:vk.height*0.12;icon_w: vk.width*0.06;
               img_source:"VirtualKeyboard/backspace.png";
               op: "dle"; Component.onCompleted: clicked.connect(buttonPressed)}

           //           VkButton {width: vk.width/10.24;icon_h:vk.height*0.12;icon_w: vk.width*0.06;img_source:"qrc:/icons/page_icon/VirtualKeyboard/backspace.png";op: "dle"; Component.onCompleted: clicked.connect(buttonPressed)}
        }
        Row {
            x: vk.width/20
            spacing: vk.width/100
           VkButton {fontSize: vk.width/20;text: "#"; op: "#"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: "$"; op: "$"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: "%"; op: "%"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: "&"; op: "&"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: "*"; op: "*"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: "-"; op: "-"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: "+"; op: "+"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: "("; op: "("; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: ")"; op: ")"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {
                width: vk.width/10.24
                op: "Back"
                img_source: "VirtualKeyboard/delete.png"
                Component.onCompleted:
                    clicked.connect(buttonPressed)
            }
        }
        Row {
            x: vk.width/100
            spacing: vk.width/100
            VkButton {
                width: vk.width/12.8
                fontSize: vk.width/20
                text: "123"
                onClicked: {
                    keyBoardStyle = 2
                    vk.x = (vkcWidth - vkcWidth_mini)/2
                    vk.y = surface.height - vkc.height
                }
            }
           VkButton {fontSize: vk.width/20;text: "<"; op: "<"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: ">"; op: ">"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: "="; op: "="; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: ":"; op: ":"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: "!"; op: "!"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: "?"; op: "?"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: ","; op: ","; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: "."; op: "."; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: "|"; op: "|"; Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {fontSize: vk.width/20;text: "~"; op: "~"; Component.onCompleted: clicked.connect(buttonPressed)}

        }
        Row {
            x: vk.width/75
            spacing: vk.width/100
            VkButton {
                width: vk.width/9.31
                fontSize: vk.width/20
                text: "A/B"
                onClicked: {
                    keyBoardStyle = 0
                }
            }
           VkButton {fontSize: vk.width/20; text: "/"; op: "/"; Component.onCompleted: clicked.connect(buttonPressed) }
           VkButton {width: vk.width/1.83;icon_h:vk.height*0.17;icon_w: vk.width*0.08;
               img_source:"VirtualKeyboard/space.png";
               op: " ";Component.onCompleted:clicked.connect(buttonPressed)}

//           VkButton {width: vk.width/1.83;icon_h:vk.height*0.17;icon_w: vk.width*0.08; img_source:"qrc:/icons/page_icon/VirtualKeyboard/space.png";op: " ";Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width/14.63;text: "_"; op: "_";Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width/7.88;
               img_source:"VirtualKeyboard/enter.png";
               op: "Enter";Component.onCompleted:clicked.connect(buttonPressed)}

           //           VkButton {width: vk.width/7.88;img_source:"qrc:/icons/page_icon/VirtualKeyboard/enter.png";op: "Enter";Component.onCompleted:clicked.connect(buttonPressed)}
        } 
    }

    //迷你键盘(密码输入)
    Column {
        id: vkcMini
        width: vkcWidth_mini
        height:vkcHeight
        anchors.top: parent.top
        spacing: vk.height/30
        visible: (keyBoardStyle===2)?true:false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 5
        Row {
            spacing: vk.width*0.01
            anchors.horizontalCenter: parent.horizontalCenter
            VkButton {
                width: vk.width*0.19
//                img_source:"qrc:/icons/page_icon/VirtualKeyboard/moveKey.png";
                text: "+";
                op: text;
                Component.onCompleted:clicked.connect(buttonPressed)
//                MouseArea {
//                    property int moveX: 0
//                    property int moveY: 0
//                    anchors.fill: parent
//                    onPressed: {
//                        moveX = mouseX
//                        moveY = mouseY
//                    }
//                    onMouseXChanged: {
//                        vk.x += mouseX - moveX
//                        vk.y += mouseY - moveY
//                    }
//                }
            }
           VkButton {width: vk.width*0.18;text: "1";op: text;Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width*0.18;text: "2";op: text;Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width*0.18;text: "3";op: text;Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width*0.19;icon_h:vk.height*0.11;icon_w: vk.width*0.06;
               img_source:"VirtualKeyboard/backspace.png"; op: "dle";Component.onCompleted:clicked.connect(buttonPressed)}

           //           VkButton {width: vk.width*0.19;icon_h:vk.height*0.11;icon_w: vk.width*0.06;img_source:"qrc:/icons/page_icon/VirtualKeyboard/backspace.png"; op: "dle";Component.onCompleted:clicked.connect(buttonPressed)}
        }

        Row {
            spacing: vk.width*0.01
            anchors.horizontalCenter: parent.horizontalCenter
           VkButton {width: vk.width*0.19; text: "-";op: text;Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width*0.18;text: "4";op: text;Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width*0.18;text: "5";op: text;Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width*0.18;text: "6";op: text;Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width*0.19;icon_h:vk.height*0.13;icon_w: vk.width*0.06;
               img_source:"VirtualKeyboard/delete.png";op: "Back";Component.onCompleted:clicked.connect(buttonPressed)}

           //           VkButton {width: vk.width*0.19;icon_h:vk.height*0.13;icon_w: vk.width*0.06;img_source:"qrc:/icons/page_icon/VirtualKeyboard/delete.png";op: "Back";Component.onCompleted:clicked.connect(buttonPressed)}
        }

        Row {
            spacing: vk.width*0.01
            anchors.horizontalCenter: parent.horizontalCenter
           VkButton {width: vk.width*0.19;text: "*";op: text;Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width*0.18;text: "7";op: text;Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width*0.18;text: "8";op: text;Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width*0.18;text: "9";op: text;Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width*0.19;text: "#";op: text;Component.onCompleted:clicked.connect(buttonPressed)}
        }

        Row {
            spacing: vk.width*0.01
            anchors.horizontalCenter: parent.horizontalCenter
            VkButton {
                width: vk.width*0.19;
                fontSize: vk.width/20
                text: "A/B"
                onClicked: {
                    keyBoardStyle = 0
                    vk.x = 0
                    vk.y = surface.height - vkc.height - y_size
                }
            }
           VkButton {width: vk.width*0.18;text: ".";op: text;Component.onCompleted: clicked.connect(buttonPressed)}
           VkButton {width: vk.width*0.18;text: "0";op: text;Component.onCompleted:clicked.connect(buttonPressed)}

           VkButton {width: vk.width*0.16;
               img_source:"VirtualKeyboard/space.png";
               op: " ";Component.onCompleted:clicked.connect(buttonPressed)}

           //           VkButton {width: vk.width*0.16;img_source:"qrc:/icons/page_icon/VirtualKeyboard/space.png";op: " ";Component.onCompleted:clicked.connect(buttonPressed)}
           VkButton {width: vk.width*0.21;icon_h:vk.height*0.12;icon_w: vk.width*0.06;
               img_source:"VirtualKeyboard/enter.png";
               op: "Enter";Component.onCompleted:clicked.connect(buttonPressed)}

           //           VkButton {width: vk.width*0.21;icon_h:vk.height*0.12;icon_w: vk.width*0.06;img_source:"qrc:/icons/page_icon/VirtualKeyboard/enter.png";op: "Enter";Component.onCompleted:clicked.connect(buttonPressed)}
        }
    }

    states: [
        State {
            name: "active"
            PropertyChanges { target: vk; y: (surface.height - vkc.height - y_size); }
        },
        State {
            name: "inactive"
            PropertyChanges { target: vk; y: surface.height; }
        }

    ]

    //按键盘上移动速度
    transitions: Transition {
        NumberAnimation {
            target: vk
            property: "y"
            easing.type: "OutQuad"
            duration: 300
        }
    }
}
