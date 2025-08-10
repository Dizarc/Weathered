import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import com.dizarc.WeatherModel
import com.dizarc.WeatherDayModel
Row {
  id: myWeatherBox

  spacing: 5

  Button {
    width: 100
    height: 20
    text: qsTr("Refresh weather")
    onClicked: {
      WeatherModel.fetchGeoData();
    }// for testing
  }

  ListView {
    id: pathView

    width: 500
    height: 1000

    model: WeatherDayModel

    delegate: WeatherDelegate {}

    // path: Path {
    //   startX: 0; startY: 100
    //   PathLine { x: pathView.width; y: 100}
    // }

    // snapMode: PathView.SnapToItem
    // highlightRangeMode: PathView.StrictlyEnforceRange
    // preferredHighlightBegin: 0.5
    // preferredHighlightEnd: 0.5
    // highlightMoveDuration: 400
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
