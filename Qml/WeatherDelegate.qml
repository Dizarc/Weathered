import QtQuick
import QtQuick.Layouts

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
        implicitHeight: 100

        clip: true

        RowLayout {
          anchors.fill: parent

          spacing: 5

          Image {
            source: weatherItemDelegate.icon

            Layout.alignment: Qt.AlignVCenter

            sourceSize.width: 100
            fillMode: Image.PreserveAspectFit
          }

          Text {
            text: weatherItemDelegate.dateTime

            Layout.alignment: Qt.AlignVCenter

            font. capitalization: Font.Capitalize
            font.pointSize: 11
            width: 100
          }

          Text {
            text: weatherItemDelegate.temp + "C"

            Layout.alignment: Qt.AlignVCenter

            font.pointSize: 11
            width: 100
          }
        }
      }
    }
  }
}
