
import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick 2.0
import com.sunwei.qmlcomponents 1.1

Rectangle
{
    id: login
    width: 699
    height: 512
    SystemPalette { id: activePalette }



    //C++组件:用户界面
    Login_Gui
    {
        id:login_gui
        onSig_login_result:
        {
            //关闭登陆动画
            load_gif.opacity = 0

            //根据登陆结果处理
            switch (result)
            {
            //登陆成功
            case 0:
                message.text = "登陆成功"
                message.opacity = 1
                break;
            //无此用户名
            case 1:
                message.text = "登陆失败:无此用户名"
                message.opacity = 1
                break;
            //密码错误
            case 2:
                message.text = "登陆失败:密码错误"
                message.opacity = 1
                break;
            //达到最大登陆次数
            case 3:
                message.text = "登陆失败:达到最大登陆次数"
                message.opacity = 1
                break;
            }
        }
    }

    //背景图片
    Image
    {
        id: background
        anchors { top: parent.top; bottom: parent.bottom }
        anchors.fill: parent
        //source: "qrc:/bkg.png"
        fillMode: Image.PreserveAspectCrop
    }

//    //消息框
//    Message
//    {
//        id: message
//        font_size: login.height * 0.03
//        anchors {centerIn: parent}
//        opacity: 0
//        visable: 0
//    }

    //登陆动画
    AnimatedImage
    {
        id: load_gif; source: "pics/load.gif"
        anchors {horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter}
        z: 100
        opacity: 0
    }

    //顶栏
    Item
    {
        id: top_bar
        width: login.width;
        height: login.height * 0.06
        anchors.top: parent.top

        Text
        {
            id: title
            anchors { top: parent.top; horizontalCenter: parent.horizontalCenter }
            text: "登陆"
            font.bold: true
            font.pointSize: login.height * 0.06 * 0.4
            color: "dark red"
        }
    }

    //空白栏
    Item
    {
        id: space1
        width: login.width;
        height: login.height * 0.1
        anchors.top: top_bar.bottom
    }

    //登陆框
    Rectangle
    {
        id: rect1
        width: login.width * 0.8;
        height: login.height * 0.3
        anchors { top: space1.bottom; horizontalCenter: parent.horizontalCenter }
        border.color: "#F07070"
        color: "transparent"
        radius: 8

        Row
        {
            spacing: rect1.width * 0.05

            Item
            {
                width: rect1.width * 0.05;
                height: rect1.height
            }

            Column
            {
                spacing: rect1.height * 0.025

                Item
                {
                    width: rect1.width * 0.8; height: rect1.height * 0.05
                }

                TextEdit
                {
                    id: txt_user_id
                    color: "#FFFFFF"

                    width: rect1.width * 0.8; height: rect1.height * 0.2
                    //font_size:height * 0.7
                    font.pixelSize: height * 0.7
                    anchors {
                        horizontalCenter: rect1.horizontalCenter;
                        top: rect1.top; topMargin: 8
                    }
                    //hint: "请输入用户号"
                    text:login_gui.user_id
                }

                TextEdit
                {
                    id: txt_password
                    color: "#FFFFFF"

                    width: rect1.width * 0.8; height: rect1.height * 0.2
                    font.pixelSize:height * 0.7
                    anchors {horizontalCenter: rect1.horizontalCenter; bottom: btn_login.top;  bottomMargin: rect1.height * 0.1}
                    //hint: "请输入密码"
                    text:login_gui.password
                }

                Row
                {
                    spacing: rect1.width * 0.1
                    Button
                    {
                        id: btn_login
                        width: rect1.width * 0.35; height: rect1.height * 0.2
                        anchors { left: rect1.left; leftMargin: 28; bottom: rect1.bottom; bottomMargin: 8 }
                        text: "登陆"
                        onClicked: login_req()
                    }

                    Button
                    {
                        id: btn_quit
                        width: rect1.width * 0.35; height: rect1.height * 0.2
                        anchors { right: rect1.right; rightMargin: 28; bottom: rect1.bottom; bottomMargin: 8 }
                        text: "退出"
                        onClicked:
                        {
                            Qt.quit();
                        }
                    }
                }

                Row
                {
                    spacing: rect1.width * 0.1

//                    CheckBox
//                    {
//                        id: check1
//                        width: rect1.width * 0.35; height: rect1.height * 0.2
//                        //anchors { left: rect1.left; top: rect1.bottom }
//                        caption: "记住密码"
//                        selected: login_gui.flag_remember
//                    }

//                    CheckBox
//                    {
//                        id: check2
//                        width: rect1.width * 0.35; height: rect1.height * 0.2
//                        //anchors { right: rect1.right; top: rect1.bottom }
//                        caption: "自动登陆"
//                        selected: login_gui.flag_auto
//                    }
                }
            }
        }
    }

    //android自带键处理
    FocusScope
    {
        focus: true

        Keys.onReleased:
        {
            if (event.key == Qt.Key_Back)
            {
                console.log("qml login quit")
                login.sig_btn_quit()
            }
        }
    }

    //登陆请求函数
    function login_req()
    {
        //判断用户名是否有效
        if (txt_user_id.text == "")
        {
            message.text = "请输入用户名"
            message.opacity = 1
            return
        }

        //判断密码是否有效
        if (txt_password.text == "")
        {
            message.text = "请输入密码"
            message.opacity = 1
            return
        }

        //显示登陆动画
        load_gif.opacity = 1

        //登陆请求
        login_gui.user_id = txt_user_id.text
        login_gui.password = txt_password.text
        login_gui.flag_remember = check1.selected
        login_gui.flag_auto = check2.selected
        login_gui.slot_login_req()
    }

//    //信号槽绑定
//    Component.onCompleted:
//    {
//        login_gui.sig_user_id_changed.connect(login_gui.slot_btn_login)
//    }
}
