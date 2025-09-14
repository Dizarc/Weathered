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
      AppController.lmManager.generateSuggestion("Athens", "Cloudy", "2025-09-01 15:00:11", 26.7, 25.6, 40.1, 2.2, 70);
    }// TODO: Remove this after testing
  }

  Text {
    text: AppController.lmManager.suggestion.length > 0 ? AppController.lmManager.suggestion
          : "Loading..."

    font.pointSize: 13
    font.weight: Font.Light
    width: 500
    height: 500
    wrapMode: Text.WordWrap
  }
}
