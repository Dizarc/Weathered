import QtQuick
import QtQuick.Controls

import com.dizarc.WeatherModel

Item {
  id: myWeatherBox

  Row{
    spacing: 5
    anchors.fill: parent
    Button {
      width: 100
      height: 20
      text: qsTr("Refresh weather")
      onClicked: WeatherModel.fetchGeoData(); // for testing
    }

    ListView {
      id: listView
      width: 500
      height: 50
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
        height: 40
        visible: true
        Row {
          anchors.fill: parent
          spacing: 5
          Text {
            text: delegate.city
            width: 150
          }
          Text {
            text: delegate.desc
            width: 150
          }
          Text {
            text: delegate.temp
            width: 150
          }
        }
      }
    }

    // Image {
    //   source: ""
    //   sourceSize.width: 50
    //   fillMode: Image.PreserveAspectFit
    // }
  }
}
