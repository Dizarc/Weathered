import QtQuick
import QtQuick.Controls

import com.dizarc.LmManager

Column {
  id: clothingBox

  spacing: 5

  Button {
    width: 100
    height: 20

    text: qsTr("Get Clothing suggestion")
    onClicked: {
      LmManager.generateSuggestion("Cloudy",26.7, 25.6, 40.1, 2.2, 70);
    } // TODO: Get these variables from the current day, current hour.
  }

  Text {
    text: LmManager.suggestion
    font.pointSize: 12
  }
}
