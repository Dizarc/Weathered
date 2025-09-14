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
      font.pixelSize: 20
      verticalAlignment: Text.AlignBottom

      text: {
        var dateObj = new Date(weatherDelegate.day);
        return dateObj.toLocaleDateString(Qt.locale(), "ddd\nMMM dd, yyyy");
      }
    }

    Loader {
      sourceComponent: currentWeatherDelegate

      onLoaded: {
        if(item && weatherDelegate.weatherItems.length > 0)
          item.weatherItem = weatherDelegate.weatherItems[0];
      }
    }

    ListView {
      id: forecastListView

      width: parent.width
      height: 120

      orientation: ListView.Horizontal
      spacing: 10

      model: weatherDelegate.weatherItems.length > 1 ?
               weatherDelegate.weatherItems.slice(1) : []

      delegate: forecastDelegate

    }

    Component {
      id: currentWeatherDelegate

      Rectangle {
        id: weatherMainItemDelegate

        property var weatherItem: null

        implicitWidth: 350
        implicitHeight: 180

        clip: true

        GridLayout {
          anchors.fill: parent

          columnSpacing: 10
          rowSpacing: 0

          columns: 2
          rows: 5

          Image {
            source: weatherMainItemDelegate.weatherItem.icon
            sourceSize.width: 100
            fillMode: Image.PreserveAspectFit
          }

          Text {
            text: weatherMainItemDelegate.weatherItem.temp + "°C"
            width: 50
            font.pointSize: 20
            font.weight: Font.DemiBold
          }

          Text {
            text: Qt.formatDate(new Date(), "yyyy-MM-dd") === weatherDelegate.day ?
                    qsTr("Now") : weatherMainItemDelegate.weatherItem.dateTime.split(" ")[1].slice(0, 5)
            width: 50
            font.pointSize: 11
            font.weight: Font.Light

            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
          }

          Text {
            text: "Feels like " + weatherMainItemDelegate.weatherItem.feelTemp + "°C"
            font.pointSize: 12
            width: 50
          }

          Text {
            text: weatherMainItemDelegate.weatherItem.desc
            width: 50
            font.capitalization: Font.Capitalize
            font.pointSize: 12

            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
          }

          Text {
            text: "Humidity " + weatherMainItemDelegate.weatherItem.humidity + "%"
            width: 50
            font.pointSize: 12
          }

          Text {
            text: "Wind speed " + weatherMainItemDelegate.weatherItem.wind + " meters/sec"
            width: 50
            font.pointSize: 12

            Layout.column: 1
            Layout.row: 3
          }

          Text {
            text: "Cloudiness " + weatherMainItemDelegate.weatherItem.clouds + "%"
            width: 50
            font.pointSize: 12

            Layout.column: 1
            Layout.row: 4
          }
        }
      }
    }

    Component {
      id: forecastDelegate

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
            width: 50
            font.pointSize: 11

            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
          }

          Image {
            source: weatherItemDelegate.icon
            sourceSize.width: 30
            fillMode: Image.PreserveAspectFit

            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
          }

          Text {
            text: weatherItemDelegate.temp + "°C"
            width: 50
            font.weight: Font.DemiBold
            font.pointSize: 10

            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
          }
        }
      }
    }
  }
}
