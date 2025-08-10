import QtQuick
import QtQuick.Layouts

import com.dizarc.Weather

Rectangle {
  id: weatherDelegate

  required property string day
  required property list<QtObject> weatherItems

  width: pathView.width
  height: 300

  Column {
    anchors.fill: parent
    spacing: 10

    Text {
      text: weatherDelegate.day
      font.bold: true
      font.pixelSize: 15
      horizontalAlignment: Text.AlignHCenter
      width: parent.width
    }

    ListView {
      id: listView
      width: parent.width
      height: parent.height - 40

      model: weatherDelegate.weatherItems

      delegate: Rectangle {
        id: weatherItemDelegate

        required property string city
        required property string desc
        required property url icon
        required property string dateTime
        required property double temp
        required property double tempMin
        required property double tempMax
        required property double humidity
        required property double wind
        required property int clouds

        width: listView.width
        implicitHeight: 50

        clip: true

        RowLayout {
          anchors.fill: parent

          spacing: 5

          Image {
            source: weatherItemDelegate.icon

            Layout.alignment: Qt.AlignVCenter

            sourceSize.width: 50
            fillMode: Image.PreserveAspectFit
          }

          Text {
            text: weatherItemDelegate.city

            Layout.alignment: Qt.AlignVCenter

            font.pointSize: 12
            width: 150
          }

          Text {
            text: weatherItemDelegate.dateTime

            Layout.alignment: Qt.AlignVCenter

            font.capitalization: Font.Capitalize
            font.pointSize: 12
            width: 150
          }

          Text {
            text: weatherItemDelegate.temp + "C"

            Layout.alignment: Qt.AlignVCenter

            font.pointSize: 12
            width: 150
          }
        }
      }
    }
  }
}
