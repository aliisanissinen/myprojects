import QtQuick 2.0

Item {

    Item {
        id: buttons
        anchors.top: lineplot.bottom
        width: insideWindow.width
        height: parent.height / 30

        SaveButtons {
            id: saveButtons
        }

        ImportDataButton {
            id: importdatabutton
        }
    }

    DrawClearButtons {
        id: drawclearbuttons
        anchors.top: buttons.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Textfieldfordata {
        id: textfieldfordata
        anchors.top: drawclearbuttons.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
    }
}
