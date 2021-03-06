import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "../../../Qml_widget"
import "../../../Qml_widget/Key_board"

import qml.custom.Page_Boot_Mode_Data 1.0

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

    signal item_clicked();

    Page_Boot_Mode_Data{
        id: data_src

        onBoot_mode_changed: {
            switch( _mode ){
            case 0:
                my_list.model.setProperty(0 ,"display",true);
                my_list.model.setProperty(1 ,"display",false);
                my_list.model.setProperty(2 ,"display",false);
                break;
            case 1:
                my_list.model.setProperty(0 ,"display",false);
                my_list.model.setProperty(1 ,"display",true);
                my_list.model.setProperty(2 ,"display",false);
                break;
            case 2:
                my_list.model.setProperty(0 ,"display",false);
                my_list.model.setProperty(1 ,"display",false);
                my_list.model.setProperty(2 ,"display",true);
                break;
            }
        }
    }

    /// 如果没有如下主动加载,也会在第一次触发定时器时被更新内容
    Component.onCompleted: {
        listview_container.focus = true;
    }

    ListModel{
        id:list_model
        ListElement{
            title:"P模式";
            value:"";
            unit:""
            display:false
        }
        ListElement{
            title:"E模式";
            value:"";
            unit:""
            display:false
        }
        ListElement{
            title:"关机前工作模式";
            value:"";
            unit:""
            display:false
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
            text: "开机模式"

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

                model:list_model;
                delegate:Switch_listView_item{
                    onItem_clicked: {
                        if ( my_list.currentIndex === 0 ){
                            data_src.p_mode_clicked();
                        } else if ( my_list.currentIndex === 1 ){
                            data_src.e_mode_clicked();
                        } else if ( my_list.currentIndex === 2 ){
                            data_src.last_mode_clicked();
                        }
                    }
                }
            }
        }
    }
}
