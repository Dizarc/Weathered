import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import com.dizarc.WeatherModel

import com.dizarc.WeatherFilterModel

Row {
  id: myWeatherBox

  spacing: 5

  Button {
    width: 100
    height: 20
    text: qsTr("Refresh weather")
    onClicked: WeatherModel.fetchGeoData(); // for testing
  }

  ListView {
    id: pathView

    width: 500
    height: 1000

    model: WeatherFilterModel

    delegate: WeatherDelegate {}
  }

  Timer {
    id: cycleTimer

    interval: 3000
    repeat: true
    running: true
    onTriggered: {
      console.log("hey")
    }
  }
}
