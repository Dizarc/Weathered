import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import com.dizarc.WeatherModel
import com.dizarc.WeatherDayModel

Column {
  id: myWeatherBox

  spacing: 5

  Button {
    width: 100
    height: 20

    text: qsTr("Refresh weather")
    onClicked: {
      WeatherModel.fetchGeoData();
    } // Only for testing
  }

  Text {
    id: cityText

    text: WeatherModel.city
    font.weight: Font.Light
    font.pixelSize: 30
    verticalAlignment: Text.AlignBottom
  }

  SwipeView {
    id: swipeView

    width: 500
    height: 1000

    clip: true
    interactive: false
    currentIndex: 0

    Repeater {
      model: WeatherDayModel

      delegate: WeatherDelegate {
        width: swipeView.width
        height: swipeView.height
      }
    }
  }

  Timer {
    id: cycleTimer

    interval: swipeView.currentIndex === 0 ? 6000 : 4000
    repeat: true
    running: true

    onTriggered: {
      swipeView.currentIndex = (swipeView.currentIndex + 1) % swipeView.count
    }
  }
}
