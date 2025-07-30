import QtQuick

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
    }
  }
}
