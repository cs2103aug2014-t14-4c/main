import QtQuick 1.0

Image {
    id: image
    source: "Images/Button_Agendaview.png"
    signal buttonClick()

    Image {
        id: imageOnClicked
        source: "Images/Button_Agendaview_Clicked.png"
        visible: false
        anchors.fill: parent
    }

    MouseArea {
        id: mouseArea
        x: 2
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
        width: 101
        height: 51
        color: "#8eb4e3"
        z: -1
    }
}
