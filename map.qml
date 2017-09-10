import QtQuick 2.0
import QtWebView 1.1

Item {
    //title: qsTr("Hello World")
    width: 1024
    height: 600
    visible: true
    property double la:30
    property double lo:116
    //latlng=40.047669,116.313082
    WebView
    {
        id:webview
        anchors.fill: parent
        url:"qrc:/ditu.html?latlng="+la+","+lo  //ditu.html是百度在线地图的代码

    }

    Component.onCompleted: {
        showalert()
    }

        function showalert()
        {

            //var js = webview.data;
            webview.runJavaScript("myalert", function(){console.log("run");});

        }


}
