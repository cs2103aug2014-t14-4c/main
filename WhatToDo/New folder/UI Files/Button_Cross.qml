import QtQuick 1.0

Image {
    id: image
    source: "Images/Button_Cross.png"
	signal buttonClick()

	Image {
		id: imageOnClicked
        source: "Images/Button_Cross_Clicked.png"
        visible: false
        anchors.fill: parent
    }
	
    MouseArea {
		id: mouseArea
		x: 9
		y: 9
		width: 47
		height: 48
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
        width: 65
        height: 65
        color: "#8eb4e3"
        z: -1
    }
}
