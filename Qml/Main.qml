import QtQuick
import QtQuick.Layouts

Window {
  id: root

  width: 640
  height: 480
  visible: true

  title: qsTr("Weathered")

  GridLayout {
    id: grid

    anchors.fill: parent

    columns: 1
    rows: 2

    WeatherBox {
      Layout.alignment: Qt.AlignLeft | Qt.AlignTop
      Layout.fillHeight: true
      Layout.fillWidth: true
    }

    QuoteBox {

      height: 500
      width: 200
      anchors.bottom: root.bottom
      //anchors.horizontalCenter: root.width
    }

  }
}
