import QtQuick 2.12
import QtQuick.Window 2.12
import Qt.labs.calendar 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Window {
    id: mainWindow
    minimumWidth: 1200
    minimumHeight: 900
    width: 1400
    height: 1000
    visible: true
    title: qsTr("Power and Weather")

    Sidebar {
        id: sidebar
        anchors.top: parent.top
        anchors.left: parent.left
    }

    InsideWindow {
        id: insideWindow
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: sidebar.right
        anchors.right: parent.right

        Lineplot {
            id: lineplot
            anchors.top : parent.top
        }
    }
}
