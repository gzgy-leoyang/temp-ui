import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.XmlListModel 2.0

import "../../../Qml_widget"
import "../../../Qml_widget/Key_board"

import qml.custom.Page_Machine_Info_Data 1.0

FocusScope{
    id:usr_setting_fs
    width:page_root.width
    height:page_root.height

    focus:true
    x:page_root.x
    y:page_root.y

    property int page_id:1
    property string page_name:   "info_query_for_usr"
    property int current_head_index: 0
    property int ddd:0
    property real underline_width: 0
    property int  underline_x: 0

    property Key_board key_board_obj: null

    Connections{
        target: key_board_obj
        onEnter_clicked:{

            if ( my_list.currentIndex === 0 ){
                data_src.machine_model = end_str;
                my_list.model.setProperty( my_list.currentIndex , "value", data_src.machine_model );
            } else if ( my_list.currentIndex === 1 ){
                data_src.machine_sn = end_str;
                my_list.model.setProperty( my_list.currentIndex , "value", data_src.machine_sn );
            }
        }
    }


    Page_Machine_Info_Data{
        id: data_src
    }

    //页面加载完成时的焦点初始位置：返回按钮
    Component.onCompleted: {
        listview_container.focus = true;
        my_list.model.setProperty(0 ,"value"    , data_src.machine_model);
        my_list.model.setProperty(1 ,"value"    , data_src.machine_sn);
    }

    ListModel{
        id:list_usr_model
        ListElement{
            type:"setting";
            title:"主机型号";
            value:"...";
            view:"";
            icon:""
            right_icon:""
        }
        ListElement{
            type:"setting";
            title:"主机序列号";
            value:"...";
            view:"";
            icon:""
            right_icon:""
        }
    }

    /*************************  页根(面)  *****************************/
    Rectangle{
        id: page_root
        width: 1280
        height: 672
        color:"#050505"
        x:0
        y:0

        /*************************  页面名称 *****************************/
        Title_row{
            id: title_row
            anchors.bottom: listview_container.top
            anchors.bottomMargin: listview_container.border.width
            text: "机器信息"

            onPicked: {
                root_stack.pop();
            }
        }

        Rectangle{
            id:listview_container
            width: page_root.width
            height: page_root.height - (   title_row.height)
            color:"#050505"
            border.width: 4;
            border.color: "#050505"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            clip: true

            ListView{
                id:my_list
                width: listview_container.width
                height: listview_container.height - 80
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 5
                clip: true

                model: list_usr_model;
                delegate:Mix_menu_list_item{
                    onItem_clicked: {
                        if ( type === "setting" ){
                            var cmp = Qt.createComponent("qrc:/Qml_widget/Key_board/Key_board.qml");
                            key_board_obj = cmp.createObject( root_rect_container,
                                                             {"key_board_style": 0,
                                                              "tips_txt": "xxxx"});
                            current_page = usr_setting_fs;
                            key_board_obj.forceActiveFocus();
                        }
                    }
                }
            }
        }
    }
}
