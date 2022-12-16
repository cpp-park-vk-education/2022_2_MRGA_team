import QtQuick 2.9
import QtQuick.Window 2.2



Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property var lastKeyBoard: letRu
    function setKeyBoard(txt) {

        if(txt === "text")
        {
//            if (lastKeyBoard !== let) // ERROR Expected token `numeric literal'
            lastKeyBoard = letRu
            lastKeyBoard.visible = true
        }
    }
}
