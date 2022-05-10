import QtQuick 6.0
import QtQuick.Window 6.0
import QtQuick.Controls 6.0 // это версия библиотеки, содержащей Contol (аналоги виджетов) для версии Qt 5.6
import QtQuick.Layouts 6.0


Window {
    id: root
    modality: Qt.ApplicationModal  // окно объявляется модальным
    title: qsTr("Добавление информации о кафе")
    minimumWidth: 400
    maximumWidth: 400
    minimumHeight: 200
    maximumHeight: 200

    GridLayout {
        anchors { left: parent.left; top: parent.top; right: parent.right; bottom: buttonCancel.top; margins: 10 }
        columns: 2

        Label {
            Layout.alignment: Qt.AlignRight  // выравнивание по правой стороне
            text: qsTr("Название кафе:")
        }
        TextField {
            id: textName
            Layout.fillWidth: true
            placeholderText: qsTr("Введите название") //текст-заполнитель строки редактирования
        }
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Адрес:")
        }
        TextField {
            id: textLenght
            Layout.fillWidth: true
            placeholderText: qsTr("Введите адрес")
        }
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Тип кухни?:")
        }
        TextField {
            id: textFlow
            Layout.fillWidth: true
            placeholderText: qsTr("Введите тип кухни")
        }
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Время работы:")
        }
        TextField {
            id: textRunoff
            Layout.fillWidth: true
            placeholderText: qsTr("Введите время работы")
        }
    }

    Button {
        visible: {textName.length>0 && textLenght.length>0} //условия отображения кнопки
        anchors { right: buttonCancel.left; verticalCenter: buttonCancel.verticalCenter; rightMargin: 10 }
        text: qsTr("Добавить в список")
        width: 100
        onClicked: {
            root.hide()
            add(textName.text, textLenght.text, textFlow.text, textRunoff.text)
        }
    }
    Button {
        id: buttonCancel
        anchors { right: parent.right; bottom: parent.bottom; rightMargin: 10; bottomMargin: 10 }
        text: qsTr("Отменить")
        width: 100
        onClicked: {
             root.hide()
        }
    }

    // изменение статуса видимости окна диалога
    onVisibleChanged: {
      if (visible) {
          textName.text = ""
          textLenght.text = ""
          textFlow.text = ""
          textRunoff.text = ""
      }
    }
 }
