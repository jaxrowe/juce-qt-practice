import QtQuick


Item
{
    id: root
    width: parent.width / 2
    height: parent.height / 2
    anchors.left : parent.horizontalCenter

    function info (count){
        text.text = count
    }
    
    Rectangle
    {
        id: rec
        width: parent.width
        height: parent.height
        anchors.left : parent.left
        color: "blue"

        Text
        {
            id: text
            anchors.centerIn: parent
            font.pointSize: 10
            text: "0"
        }

        
    }
}