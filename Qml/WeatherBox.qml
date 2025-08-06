import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import com.dizarc.WeatherModel

Row{
  id: myWeatherBox

  spacing: 5

  Button {
    width: 100
    height: 20
    text: qsTr("Refresh weather")
    onClicked: WeatherModel.fetchGeoData(); // for testing
  }

  ListView {
    id: listView

    width: 500

    model: WeatherModel

    delegate: Rectangle {
      id: delegate

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
          source: delegate.icon

          Layout.alignment: Qt.AlignVCenter

          sourceSize.width: 50
          fillMode: Image.PreserveAspectFit
        }

        Text {
          text: delegate.city

          Layout.alignment: Qt.AlignVCenter

          font.pointSize: 12
          width: 150
        }
        Text {
          text: delegate.desc

          Layout.alignment: Qt.AlignVCenter

          font.capitalization: Font.Capitalize
          font.pointSize: 12
          width: 150
        }
        Text {
          text: delegate.temp + "C"

          Layout.alignment: Qt.AlignVCenter

          font.pointSize: 12
          width: 150
        }
      }
    }
  }
}
