import QtQuick

import com.dizarc.AppController

Column {
  id: myNewsBox

  spacing: 5

  ListView {
    id: listView

    width: 500
    height: 500
    spacing: 20
    interactive: false

    model: AppController.newsModel

    delegate: NewsDelegate {
      width: listView.width
      height: 120
    }
  }

}
