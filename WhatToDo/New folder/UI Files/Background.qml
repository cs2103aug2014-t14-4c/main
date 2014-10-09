import QtQuick 1.0

Image {
    id: image
    source: "Images/Background.png"
	
    BorderImage {
        id: imageCommandline
        x: 18
        y: 551
        width: 922
        height: 115
        source: "Images/Textfield_Commandline.png"
    }

    Image {
        id: imageDisplay
        x: 18
        y: 104
        width: 922
        height: 435
        source: "Images/Textfield_Display.png"
    }

    Image {
        id: imageSearchbox
        x: 588
        y: 25
        width: 352
        height: 58
        source: "Images/Textfield_Searchbox.png"
    }
	
}
