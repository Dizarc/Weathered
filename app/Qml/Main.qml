import QtQuick
import QtQuick.Layouts

Window {
  id: root

  width: 1000
  height: 1000
  visible: true

  title: qsTr("Weathered")

    GridLayout {
      anchors.fill: parent

      columns: 2
      rows: 2
      columnSpacing: 10
      rowSpacing: 10

      WeatherBox {
        Layout.preferredWidth: 500
        Layout.preferredHeight: 800
      }

      ClothingBox {
        Layout.preferredWidth: 500
        Layout.preferredHeight: 500
        Layout.alignment: Qt.AlignRight | Qt.AlignTop
      }

      QuoteBox {
        Layout.preferredWidth: 300
        Layout.preferredHeight: 300
        Layout.columnSpan: 2
        Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
      }
    }


}
