import QtQuick 2.5
import QtQuick.Window 2.2


Window
{
    visible: true
    width: Screen.width / 2
    height: Screen.width / 2
    color:"black"
    // put main window it in the center
    x:Screen.width/2 - width/2
    y:Screen.height/2 - height/2


    MNode
    {
        x:100
        y:200
        dwidth: 200
        dheight: 120
        dname:"Houdini"
        bgcolor: "black"
        dtext: "Note that the TextEdit does not implement scrolling, following the cursor to add flickable scrolling that follows the cursor:"

    }

    MNode
    {

        x:600
        y:300
        dwidth: 100
        dheight: 120
        dname:"Maya"
        bgcolor: "#505050"
    }
    MNode
    {
        x:400
        y:700
        dwidth: 300
        dheight: 100
        dname: "Shit"
        bgcolor: "#002266"
        dtext: "are you want shit"
    }


}
