import QtQuick
import QtQuick.Controls

import com.dizarc.WeatherModel

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
        //text: WeatherModel.info
        font.pointSize: 15
      }

      Button {
        width: 50
        onClicked: WeatherModel.fetchGeoData(); // for testing
      }
    }
  }
}
