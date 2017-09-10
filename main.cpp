#include <QGuiApplication>
#include <QQmlApplicationEngine>


//#include "world.h"
//#include "main_gui.h"
#include "login_gui.h"
//#include "light_gui.h"
//#include "heart_beat.h"
//#include "net.h"
//#include "data_sync_center.h"
//#include "set_ctrl_state.h"

#include <QQuickView>
#include <QApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //注册组件到QML
    qmlRegisterType<Login_Gui>("com.sunwei.qmlcomponents", 1, 1, "Login_Gui");
    //qmlRegisterType<MySliderItem>("com.mycompany.qmlcomponents", 1, 0, "Slider");

    QQuickView viewer;
    viewer.setSource(QUrl("qrc:/map.qml"));

    viewer.show();

    return app.exec();
}
