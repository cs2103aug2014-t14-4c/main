import QtQuick 1.0

Item {
    id: feedbackBox
    x: 0
    y: 0
    width: 911
    height: 421
    property bool isStartAnimation: false
    property double imageOpacity: 0.0
    property string userMessage: ""

    Image {
        id: feedbackImage
        x: 0
        y: feedbackBox.height
        width: 0
        height: 0
        source: "Images/Msgbox_Feedback.png"
        opacity: feedbackBox.imageOpacity
        property double maxWidth: 320
        property double maxHeight: 155

        Text {
            id: userMessageText
            x: feedbackImage.width*0.1
            y: feedbackImage.height*0.1
            width: feedbackImage.width*0.8
            height: feedbackImage.height*0.7
            text: feedbackBox.userMessage
            z: 3
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 10*(userMessageText.width)/(feedbackImage.width*0.8)
            font.family: "Calibri"
            opacity: 0
        }

        SequentialAnimation {
             running: feedbackBox.isStartAnimation
             ParallelAnimation {
                 running: feedbackBox.isStartAnimation
                 NumberAnimation { target: feedbackImage; property: "x"; to: 330; duration: 250 }
                 NumberAnimation { target: feedbackImage; property: "y"; to: 156; duration: 250 }
                 NumberAnimation { target: feedbackImage; property: "width"; to: feedbackImage.maxWidth*0.7; duration: 250 }
                 NumberAnimation { target: feedbackImage; property: "height"; to: feedbackImage.maxHeight*0.7; duration: 250 }
             }
             NumberAnimation { target: userMessageText; property: "opacity"; to: 1.0; duration: 10 }
             NumberAnimation { target: feedbackImage; property: "y"; to: 156; duration: 1500 }
             NumberAnimation { target: feedbackBox; property: "imageOpacity"; to: 0.5; duration: 1000 }
             ParallelAnimation {
                 running: feedbackBox.isStartAnimation
                 NumberAnimation { target: feedbackImage; property: "x"; to: 0; duration: 250 }
                 NumberAnimation { target: feedbackImage; property: "y"; to: feedbackBox.height; duration: 250 }
                 NumberAnimation { target: feedbackImage; property: "width"; to: 0; duration: 250 }
                 NumberAnimation { target: feedbackImage; property: "height"; to: 0; duration: 250 }
                 NumberAnimation { target: userMessageText; property: "opacity"; to: 0.0; duration: 10 }
             }
             NumberAnimation { target: feedbackBox; property: "isStartAnimation"; to: 0; duration: 10 }
             NumberAnimation { target: feedbackBox; property: "imageOpacity"; to: 0.0; duration: 10 }
        }
    }
}


