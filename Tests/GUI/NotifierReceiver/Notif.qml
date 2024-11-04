import QtQuick


Item
{
    id: root
    width: parent.width / 2
    height: parent.height / 2
    anchors.left : parent.left

    property int count : 0

    // nest Receiver class as 'target'
    // connect notify to info function
    required property Receiver target
    onTargetChanged:
    {
        notify.connect(target.info)
    }

    signal notify(string count)

    Rectangle
    {
        id: notif
        width: parent.width
        height: parent.height
        anchors.left : parent.left
        color: "red"

        Text
        {
            id: text
            anchors.centerIn: parent
            font.pointSize: 10
            text: root.count
        }

        MouseArea
        {
            anchors.fill: parent
            onClicked :
            {
                root.count++
                notify(root.count)
            }
        }
        
    }
}