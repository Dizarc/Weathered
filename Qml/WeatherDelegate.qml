import QtQuick
import QtQuick.Layouts

import Qt.labs.qmlmodels

Rectangle {
  id: weatherDelegate

  required property string day
  required property list<QtObject> weatherItems

  Column {
    anchors.fill: parent
    spacing: 10

    Text {
      font.pixelSize: 15
      verticalAlignment: Text.AlignBottom

      text: {
        var dateObj = new Date(weatherDelegate.day);
        return dateObj.toLocaleDateString(Qt.locale(), "ddd\nMMM dd, yyyy");
      }
    }

    ListView {
      id: listView

      width: parent.width - 40
      height: parent.height - 40

      orientation: ListView.Horizontal

      model: weatherDelegate.weatherItems
      delegate: chooser

      DelegateChooser {
        id: chooser

        // TODO: Create the delegate for current weather
        //DelegateChoice {
          //row: 0
        //}

        DelegateChoice {
          Rectangle {
            id: weatherItemDelegate

            required property url icon
            required property string dateTime
            required property double temp

            implicitWidth: 50
            implicitHeight: 100

            clip: true

            ColumnLayout {
              anchors.fill: parent

              spacing: 5

              Text {
                text: weatherItemDelegate.dateTime.split(" ")[1].slice(0, 5)

                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font. capitalization: Font.Capitalize
                font.pointSize: 11
                width: 50
              }

              Image {
                source: weatherItemDelegate.icon

                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                sourceSize.width: 30
                fillMode: Image.PreserveAspectFit
              }

              Text {
                text: weatherItemDelegate.temp + "°C"

                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pointSize: 10
                width: 50
              }
            }
          }
        }
      }
    }
  }
}
