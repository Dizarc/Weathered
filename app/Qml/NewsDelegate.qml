import QtQuick
import QtQuick.Layouts

ColumnLayout {
  id: myNewsDelegate

  required property string title
  required property string desc
  required property string dateTime
  required property string source

  Text {
    font.pointSize: 10
    font.weight: Font.Light

    text: {
      var dateObj = new Date(dateTime);
      return dateObj.toLocaleDateString(Qt.locale(), Locale.LongFormat)
    }
  }

  Text {
    font.pointSize: 12
    font.weight: Font.DemiBold
    wrapMode: Text.WordWrap
    Layout.fillWidth: true

    text: title
  }

  Text {
    font.pointSize: 10
    wrapMode: Text.WordWrap
    Layout.fillWidth: true

    text: desc
  }

  Text {
    font.pointSize: 9

    text: "By: " + source
  }

}
