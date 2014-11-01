import QtQuick 1.0

Item {
    id: actionBox
    x: 0
    y: 0
    width: 911
    height: 421
    property bool isStartAnimation: false
    property double imageOpacity: 0.0
    property string actionMessage: ""

    Image {
        id: actionImage
        x: 0
        y: actionBox.height
        width: 0
        height: 0
        source: "Images/Msgbox_Action.png"
        opacity: actionBox.imageOpacity
        property double maxWidth: 320
        property double maxHeight: 155

        Text {
            id: userMessageText
            x: actionImage.width*0.1
            y: actionImage.height*0.1
            width: actionImage.width*0.8
            height: actionImage.height*0.7
            text: actionBox.actionMessage
            z: 3
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 10*(userMessageText.width)/(actionImage.width*0.8)
            font.family: "Calibri"
            opacity: 0
        }

        SequentialAnimation {
             running: actionBox.isStartAnimation
             ParallelAnimation {
                 running: actionBox.isStartAnimation
                 NumberAnimation { target: actionImage; property: "x"; to: 330; duration: 250 }
                 NumberAnimation { target: actionImage; property: "y"; to: 156; duration: 250 }
                 NumberAnimation { target: actionImage; property: "width"; to: actionImage.maxWidth*0.7; duration: 250 }
                 NumberAnimation { target: actionImage; property: "height"; to: actionImage.maxHeight*0.7; duration: 250 }
             }
             NumberAnimation { target: userMessageText; property: "opacity"; to: 1.0; duration: 10 }
             NumberAnimation { target: actionImage; property: "y"; to: 156; duration: 600 }
             NumberAnimation { target: actionBox; property: "imageOpacity"; to: 0.5; duration: 500 }
             ParallelAnimation {
                 running: actionBox.isStartAnimation
                 NumberAnimation { target: actionImage; property: "x"; to: 0; duration: 250 }
                 NumberAnimation { target: actionImage; property: "y"; to: actionBox.height; duration: 250 }
                 NumberAnimation { target: actionImage; property: "width"; to: 0; duration: 250 }
                 NumberAnimation { target: actionImage; property: "height"; to: 0; duration: 250 }
                 NumberAnimation { target: userMessageText; property: "opacity"; to: 0.0; duration: 10 }
             }
             NumberAnimation { target: actionBox; property: "isStartAnimation"; to: 0; duration: 10 }
             NumberAnimation { target: actionBox; property: "imageOpacity"; to: 0.0; duration: 10 }
        }
    }
}


