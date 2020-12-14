import QtQuick 2.7

/*描述：此组件为虚拟键盘，分为26键大写字母(0 默认)、26键小写字母(0 需要使用shift切换)、一行数字和符号(1)、九宫格数字键盘(2) 共4种样式  ；
 *样式初始化：key_board_style: x  #x为以上描述样式编号
 *带输入框：have_input_rect = true
 *提示语：tips_txt = "xxxxxx"
*/

FocusScope{
    id:key_board_fs
    width: 1280
    height: 800
//    y:1280

    property alias key_board_style: key_board.keyBoardStyle

    property Item parent_page: root_stack.currentItem
    property bool have_input_rect: true
    property string init_string: ""
    property string endding_string: ""
    property string tips_txt: ""                    ///输入字符串类型/内容等提示
    property string tips_color: "#00FFFF"           ///输入字符串类型/内容等提示文字颜色

    property string parent_item_name: ""

    signal enter_clicked(string parent_item, string end_str);
    signal str_lenth_changed(string end_str);
    signal obj_showed();
    signal obj_start_hide();


    Connections{
        target: root_stack
        onCurrentItemChanged:{
            key_board_fs.destroy();
        }
    }

    onFocusChanged: {
        if(key_board_fs.activeFocus){
            animation_show.running = true
//            console.log("show")
        }
        else {
//             console.log("hide")
        }
    }


    PropertyAnimation {
        id: animation_show
        target: key_board_fs
        property: "y";
        duration: 450;
        from: 1280;
        to: 0;
        easing.type: Easing.InOutQuad;
        running: false;
        onStopped: {
            obj_showed()
        }
    }

    PropertyAnimation {
        id: animation_hide
        target: key_board_fs
        property: "y";
        duration: 450;
        from: 0;
        to: 1280;
        easing.type: Easing.InOutQuad;
        running: false;
        onStopped: {
            key_board_fs.destroy();
            parent_page.forceActiveFocus();
        }
    }

    Component.onCompleted: {
        edit.text = init_string;
    }

    Rectangle{
        id: covery
        width: 720
        anchors.top:parent.top

        color: "transparent"
        anchors.bottom: key_board_container.top
        MouseArea{
            anchors.fill: parent
            onClicked: {
                obj_start_hide();
                animation_hide.running = true
            }
        }
    }

    Rectangle{
        id: key_board_container
        height: 500//464
        width: 720
        color: "#333333"//"#5f5252"
        anchors.bottom: parent.bottom
        MouseArea{
            anchors.fill: parent
            onClicked: {
            }
        }

        Text{
            id: tips
            text: tips_txt
            color: tips_color
            font.pixelSize: 30
            anchors.top:parent.top
//            anchors.left:parent.left
//            anchors.leftMargin: 55
            anchors.horizontalCenter: parent.horizontalCenter
        }

        VirtualKeyboard{
            id: key_board
            height: 370
            width: 720

            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            onButtonPressed: {
                switch(op){
                case "dle":
                    edit.remove(edit.cursorPosition-1, edit.cursorPosition);
                    break;
                case "Back" :
                    edit.clear();
                    break;
                case "Enter" :
                    enter_clicked(key_board_fs.parent_item_name, endding_string);
                    animation_hide.running = true
                    obj_start_hide()
                    break;  //确认
                default:
                    edit.insert(edit.cursorPosition, op);
                    break;
                }
            }
        }
        Rectangle{
            width: 600
            height: 65
            color: "gray"
            radius: 15
            anchors.bottom: key_board.top
            anchors.bottomMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            visible: have_input_rect
            TextEdit {
                id: edit
                width: parent.width - 6
                text: ""
                color: "black"
                font.family: "Helvetica"
                font.pointSize: 30
                focus: true
                anchors.centerIn: parent
                cursorPosition:text.length
                clip: true
                onLengthChanged: {
                    endding_string = edit.text;
                    str_lenth_changed(endding_string);
                }
            }
        }
    }
}

