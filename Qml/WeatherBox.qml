import QtQuick
import QtQuick.Controls

import com.dizarc.WeatherApi

Item {
  id: myWeatherBox

  Rectangle {
    anchors.fill: parent
    Row{
      spacing: 5

      Image {
        source: ""
        sourceSize.width: 50
        fillMode: Image.PreserveAspectFit
      }

      Text {
        text: WeatherApi.info
        font.pointSize: 15
      }

      Button {
        width: 50
        onClicked: WeatherApi.fetchGeoData(); // for testing
      }
    }
  }
}
