import QtQuick 1.0

Image {
    id: image
    source: "Images/Msgbox_Feedback.png"
    signal finished()
    property bool animateopacity: true
    property string usermessage: "Testing hahahah one two three"
    property double imageopacity: 0.50
    opacity: imageopacity

    Text {
        id: text1
        x: 14
        y: 8
        width: 252
        height: 108
        text: image.usermessage
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 11
        font.family: "Calibri"
    }

    Behavior on opacity {
        enabled: animateopacity
        NumberAnimation { duration: 1800 }
    }
}
