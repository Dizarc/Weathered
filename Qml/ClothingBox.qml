import QtQuick
import QtQuick.Controls

import com.dizarc.AppController

Column {
  id: clothingBox

  spacing: 5

  Button {
    width: 100
    height: 20

    text: qsTr("Get Clothing suggestion")
    onClicked: {
      AppController.lmManager.generateSuggestion("Cloudy",26.7, 25.6, 40.1, 2.2, 70);
    } // TODO: Get these variables from the current day, current hour.
  }

  Text {
    text: AppController.lmManager.suggestion.length > 0 ? AppController.lmManager.suggestion
          : "Loading..."
    font.pointSize: 12
    wrapMode: Text.WordWrap
  }
}
