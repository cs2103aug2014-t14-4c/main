import QtQuick 1.0

Image {
    id: image
    source: "Images/Button_Enter.png"
    signal buttonClick()

	Image {
		id: imageOnClicked
		source: "Images/Button_Enter_Clicked.png"
		visible: false
		anchors.fill: parent
	}
	
    MouseArea {
        id: mouseArea
        x: 8
        y: 8
        width: 97
        height: 50
        onPressed: {
            imageOnClicked.visible = true
        }
		onReleased: {
			image.buttonClick();
			imageOnClicked.visible = false
		}
    }
}
