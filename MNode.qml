import QtQuick 2.0

Item
{
    id:defNode
    property int dwidth
    property int dheight
    property string dname
    property string bgcolor
    property string dtext : "bad news"

    property int radius: 8
    width: dwidth
    height: dheight


   // main bound rect
    Rectangle
    {
        id:rect
        anchors.fill: parent
        border.color: "#FFFFFF"
        border.width: 1
        color:bgcolor
        radius:defNode.radius
        opacity: 0.9
        scale:parent.scale

    }

    // header rect
    Rectangle
    {
        id:header
        width:rect.width
        height: 20
        //color:"white"
        opacity: 0.7
        radius:defNode.radius
        scale: rect.scale

        gradient: Gradient
        {
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 0.1; color: "white" }
            GradientStop { position: 0.3; color: "#BBBBBB" }
            GradientStop { position: 1.0; color: "lightsteelblue" }
        }
    }

    // circle output
    Rectangle
    {
        property int _radius : 15
       // var _radius = 5

        id:cicle
        radius:_radius
        width:_radius
        height:_radius
        opacity: 1
        anchors.horizontalCenter: rect.horizontalCenter
        anchors.top:rect.bottom
        border.color: "brown"
        border.width: 1


    }


    Text {
        anchors.centerIn: header
        id: nodeName
        text: defNode.dname
        color:"#FFFFFF"
        font.bold:true
    }

    // Edit Text is here
    Rectangle
    {
        id:myedit
        height : rect.height - header.height
        width : rect.width
        anchors.top: header.bottom
        opacity: 0.1

    }

    TextEdit
    {
        width:myedit.width
        text: defNode.dtext
        wrapMode: TextEdit.WrapAnywhere
        focus: true
        color:"#FFFFFF"
        opacity: 1
        anchors.fill: myedit
        anchors.margins: 6
        scale: rect.scale
    }


    MouseArea
    {
        property int isPress: 0
        property point clickPos: "0,0"
        id:marea
        anchors.fill: header
        hoverEnabled: true
        onEntered:
        {
            defNode.scale = 1.05
        }
        onExited:
        {
            defNode.scale =1
        }


        onPressed:
        {
            isPress = true
            clickPos = Qt.point(mouse.x,mouse.y)
            rect.border.color = "yellow"
        }

        onPositionChanged:
        {
            if(isPress)
            {
                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                defNode.x = defNode.x + delta.x
                defNode.y = defNode.y + delta.y
            }
        }
        onReleased:
        {
            isPress = false
            rect.border.color = "#FFFFFF"
        }

    }



}
