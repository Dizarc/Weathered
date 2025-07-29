import QtQuick

Item {
  id: myWeatherBox

  Rectangle {
    anchors.fill: parent
    Row{
      spacing: 5

      Image {
        source: ""
        sourceSize.width: 50
        fillMode: Image.PreserveAspectFit
      }

      Text {
        text: qsTr("15C")
        font.pointSize: 15
      }
    }
  }
}
