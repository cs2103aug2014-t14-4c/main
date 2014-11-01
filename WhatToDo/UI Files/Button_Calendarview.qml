import QtQuick 1.0

Image {
    id: image
    source: "Images/Button_Calendarview.png"
    signal buttonClick()

    Image {
        id: imageOnClicked
        source: "Images/Button_Calendarview_Clicked.png"
        visible: false
        anchors.fill: parent
    }

    MouseArea {
        id: mouseArea
        x: 3
        y: 5
        width: 97
        height: 42
        onPressed: {
            imageOnClicked.visible = true
        }
        onReleased: {
            image.buttonClick();
            imageOnClicked.visible = false
        }
    }

    Rectangle {
        id: rectangle1
        x: 0
        y: 0
        width: 102
        height: 51
        color: "#7F7F7F"
        z: -1
    }
}
