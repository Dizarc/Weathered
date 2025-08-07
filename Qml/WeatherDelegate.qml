import QtQuick
import QtQuick.Layouts

Rectangle {
      id: weatherDelegate

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

      width: pathView.width
      implicitHeight: 50

      clip: true

      RowLayout {
        anchors.fill: parent

        spacing: 5

        Image {
          source: weatherDelegate.icon

          Layout.alignment: Qt.AlignVCenter

          sourceSize.width: 50
          fillMode: Image.PreserveAspectFit
        }

        Text {
          text: weatherDelegate.city

          Layout.alignment: Qt.AlignVCenter

          font.pointSize: 12
          width: 150
        }
        Text {
          text: weatherDelegate.desc

          Layout.alignment: Qt.AlignVCenter

          font.capitalization: Font.Capitalize
          font.pointSize: 12
          width: 150
        }
        Text {
          text: weatherDelegate.temp + "C"

          Layout.alignment: Qt.AlignVCenter

          font.pointSize: 12
          width: 150
        }
      }
    }
