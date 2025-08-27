import QtQuick
import QtQuick.Controls

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
    font.pointSize: 15
  }
}
