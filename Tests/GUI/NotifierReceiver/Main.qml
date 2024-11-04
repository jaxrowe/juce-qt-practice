import QtQuick
import NotifRec

Window 
{
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Notif
    {
        id: notif
        target : receiver
    }

    Receiver
    {
        id : receiver
    }
}


// 1. when Notif instanced, the required property `target` is set to the instanced Receiver
// 2. onTargetChanged inside Notif is called, and makes Notif.notify call Receiver.info
// 3. Notif.MouseArea.OnClicked() emits Notif.notify signal, pass 'count'
// 4. the nofity signal calls Receiver.info function