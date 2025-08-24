import QtQuick
import QtQuick.Controls

import com.dizarc.LmManager

Column {
  id: quoteBox

  spacing: 5

  Button {
    width: 100
    height: 20

    text: qsTr("Get Quote")
    onClicked: {
      LmManager.generateQuote();
    } // TODO: Remove this after testing
  }

  Text {
    text: LmManager.quote
    font.pointSize: 15
  }
}
