import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: dlg_root
    width: 1280
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

    Loader {
        sourceComponent: {
            switch(type) {
                case "page"     :
                    return type_page;
                case "setting"  :
                    return type_setting;
                case "popUp"    :
                    return type_popUp;
                case "switch"   :
                    return type_switch;
                case "info"     :
                    return type_info;
                case "doubt_page":
                    return type_page;
            }
        }
    }

    Component{
        id: type_page

        Rectangle{
            id: type_page_container
            width:dlg_root.width
            height: dlg_root.height
            color: "transparent"
            border.width: 4
            border.color: "transparent"
            property alias line_x: line.x
            Image{
                id:m_img;
                source: icon;
                height: 48
                width: icon === "" ? 0 : 48
                anchors.left: parent.left;
                anchors.leftMargin: 15;
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectCrop  //可以裁减
            }

            Text {
                id:m_name
                text:title
                anchors.left: icon === "" ? parent.left :  m_img.right;
                anchors.leftMargin : 20;
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                color: text_color
                font.family: "Ubuntu"
                font.pixelSize: font_size
            }

            Image{
                id:m_right_image;
                source: right_icon;

                anchors.right: parent.right;
                anchors.rightMargin: 10;
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectCrop  //可以裁减
            }

            Rectangle{
                id: line
                height: 1
                anchors.left: m_name.left
                anchors.right: m_right_image.right
                anchors.rightMargin: 30
                anchors.bottom: parent.bottom
                color: "grey"
                opacity: 0.5

                Component.onCompleted: {
                    line_width = width
                    line_x = x
                }
            }
        }
    }

    Component{
        id: type_setting
        Rectangle{
            id: type_setting_container
            width:dlg_root.width
            height: dlg_root.height
            color: "transparent"
            border.width: 4
            border.color: "transparent"

            Image{
                id:m_img;
                source: icon;
                height: 48
                width: 48
                anchors.left: parent.left;
                anchors.leftMargin: 15;
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectCrop  //可以裁减
            }

            Text {
                id:m_name
                text:title

                anchors.left: icon === "" ? parent.left : m_img.right;
                anchors.leftMargin: 20;
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                color: text_color
                font.family: "Ubuntu"
                font.pixelSize: font_size
            }

            Text {
                id:m_val
                text:value

                anchors.right: parent.right
                anchors.rightMargin: 20;
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                color: text_color
                font.family: "Ubuntu"
                font.pixelSize: font_size
            }


            Rectangle{
                id: line
                height: 1
                anchors.left: m_name.left
                anchors.right: m_val.right
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
    }

    Component{
        id: type_popUp
        Rectangle{
            id: type_popUp_container
            width:dlg_root.width
            height: dlg_root.height
            color: "transparent"
            border.width: 4
            border.color: "transparent"

            Image{
                id:m_img;
                source: icon;
                height: 48
                width: 48
                anchors.left: parent.left;
                anchors.leftMargin: 15;
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectCrop  //可以裁减
            }

            Text {
                id:m_name
                text:title

                anchors.left: icon === "" ? parent.left : m_img.right;
                anchors.leftMargin: 20;
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                color: text_color
                font.family: "Ubuntu"
                font.pixelSize: font_size
            }

            Text {
                id:m_val
                text:value

                anchors.right: parent.right
                anchors.rightMargin: 20;
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                color: text_color
                font.family: "Ubuntu"
                font.pixelSize: font_size
            }

            Rectangle{
                id: line
                height: 1
                anchors.left: m_name.left
                anchors.right: m_val.right
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
    }

    /////////////////
    Component{
        id: type_switch

        Rectangle{
            id: type_switch_container
            width:dlg_root.width
            height: dlg_root.height
            color: "transparent"
            border.width: 4
            border.color: "transparent"

            Image{
                id:m_img;
                source: icon;
                height: 48
                width: 48
                anchors.left: parent.left;
                anchors.leftMargin: 15;
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectCrop  //可以裁减
            }

            Text {
                id:m_name
                text:title

                anchors.left: icon === "" ? parent.left : m_img.right;
                anchors.leftMargin: 20;
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                color: text_color
                font.family: "Ubuntu"
                font.pixelSize: font_size
            }

            Switcher{
                id: control
                available: true;
                checked_val: (value==="1")?true:false;

                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle{
                id: line
                height: 1
                anchors.left: m_name.left
                anchors.right: control.right
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
    }

    Component{
        id: type_info
        Rectangle{
            id: type_type_info_container
            width:dlg_root.width
            height: dlg_root.height
            color: "transparent"
            border.width: 4
            border.color: "transparent"

            Image{
                id:m_img;
                source: icon;
                height: 48
                width: 48
                anchors.left: parent.left;
                anchors.leftMargin: 15;
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectCrop  //可以裁减
            }

            Text {
                id:m_name
                text:title

                anchors.left: icon === "" ? parent.left : m_img.right;
                anchors.leftMargin: 20;
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                color: text_color
                font.family: "Ubuntu"
                font.pixelSize: font_size
            }

            Text {
                id:m_val
                text:value

                anchors.right: parent.right
                anchors.rightMargin: 20;
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                color: text_color
                font.family: "Ubuntu"
                font.pixelSize: font_size
            }


            Rectangle{
                id: line
                height: 1
                anchors.left: m_name.left
                anchors.right: m_val.right
                anchors.bottom: parent.bottom
                color: "grey"
                opacity: 0.5
                Component.onCompleted: {
                    line_width = width
                    line_x = x
                }
            }
        }
    }

    onFocusChanged: {
//        headIndexChanged();
    }

    MouseArea{
        anchors.fill: parent;
        onClicked: {
            my_list.focus = true;
            my_list.currentIndex = index;
//            if(type === "popUp"){
//                cmp_obj = Qt.createComponent( view );
//                page_obj = cmp_obj.createObject(root_rect_container,{});
//                current_page = root_stack.currentItem;
//                page_obj.forceActiveFocus();
//            } else
                if(type === "page"){
                cmp_obj = Qt.createComponent( view );
                page_obj = cmp_obj.createObject(root_rect_container,{});
                root_stack.push({item:page_obj, destroyOnPop:true});
            } else if(type === "switch"){
                item_switch_checked();
            } else {
                item_clicked();
            }
        }
    }

    Keys.onPressed:{
        if (event.key === Qt.Key_Space){
            my_list.focus = true;
            my_list.currentIndex = index;
//            if(type === "popUp"){
//                cmp_obj = Qt.createComponent( view );
//                page_obj = cmp_obj.createObject(root_rect_container,{});
//                current_page = root_stack.currentItem;
//                page_obj.forceActiveFocus();
//            } else
                if(type === "page"){
                cmp_obj = Qt.createComponent( view );
                page_obj = cmp_obj.createObject(root_rect_container,{});
                root_stack.push({item:page_obj, destroyOnPop:true});
            } else if(type === "switch"){
                item_switch_checked();
            } else {
                item_clicked();
            }
        }
    }  
}

