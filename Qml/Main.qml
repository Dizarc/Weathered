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

    // TODO: Add Quote box for the quotes from QuoteManager
    Text {
      Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
      text: qsTr("The quote will go here")
      font.pointSize: 15
    }

  }
}
