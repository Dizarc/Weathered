import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import com.dizarc.AppController

Column {
  id: myWeatherBox

  spacing: 5

  Text {
    id: cityText

    text: AppController.weatherModel.city
    font.weight: Font.Light
    font.pixelSize: 40

    verticalAlignment: Text.AlignBottom
  }

  SwipeView {
    id: swipeView

    width: 1000
    height: 1000

    clip: true
    interactive: false
    currentIndex: 0

    Repeater {
      model: AppController.weatherDayModel

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
