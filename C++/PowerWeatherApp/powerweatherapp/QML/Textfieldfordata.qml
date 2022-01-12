import QtQuick 2.0
import QtQuick.Controls 2.12

Item
{
    property alias textToUserText: textToUser.text

    width: insideWindow.width
    height: parent.height / 5

    Rectangle {
        id: background
        width: parent.width
        height: parent.height
        color: "lightblue"

        Text {
            id: textToUser
            text: `${(statistics.textToUser)}`
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }
}
