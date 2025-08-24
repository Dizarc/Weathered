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

    columns: 2
    rows: 2

    WeatherBox {
      Layout.alignment: Qt.AlignLeft | Qt.AlignTop
      Layout.fillHeight: true
      Layout.fillWidth: true
    }

    ClothingBox {
      Layout.alignment: Qt.AlignRight | Qt.AlignTop
      height: 500
      width: 300
    }

    QuoteBox {

      height: 500
      width: 200
      anchors.bottom: root.bottom
      //anchors.horizontalCenter: root.width
    }

  }
}
