import QtQuick
import QtQuick.Controls

import com.dizarc.QuoteManager

Column {
  id: quoteBox

  spacing: 5

  Button {
    width: 100
    height: 20

    text: qsTr("Get Quote")
    onClicked: {
      QuoteManager.generateQuote();
    } // TODO: Remove this after testing
  }

  Text {
    //text: QuoteManager.quote();
    font.pointSize: 15
  }
}
