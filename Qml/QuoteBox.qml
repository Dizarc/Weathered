import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import com.dizarc.AppController

Column {
  id: quoteBox

  spacing: 5
  Button {
    width: 100
    height: 20

    text: qsTr("Get Quote")
    onClicked: {
      AppController.lmManager.generateQuote();
    } // TODO: Remove this after testing
  }
  Text {
    text: AppController.lmManager.quote
    width: 300
    height: 300
    wrapMode: Text.WordWrap
    font.weight: Font.Light
    font.pointSize: 15
  }
}
