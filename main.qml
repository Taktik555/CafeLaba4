import QtQuick 6.0
import QtQuick.Window 6.0
import QtQuick.Controls 6.0// это версия библиотеки, содержащей Contol (аналоги виджетов) для версии Qt 5.6
import QtQuick.Layouts 6.0

Window {
    visible: true
    width: 800
    height: 550
    title: qsTr("Справочник кафе города")

    // объявляется системная палитра
    SystemPalette {
          id: palette;
          colorGroup: SystemPalette.Active
       }

    Rectangle{
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: butAdd.top
        anchors.bottomMargin: 8
        border.color: "SteelBlue"


    ScrollView {
        anchors.fill: parent
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        Text {
            anchors.fill: parent
            text: "Could not connect to SQL"
            color: "red"
            font.pointSize: 20
            font.bold: true
            visible: IsConnectionOpen == false
        }
        ListView {
            id: rivList
            anchors.fill: parent
            model: cafeModel // назначение модели, данные которой отображаются списком
            delegate: DelegateForCafe{}
            clip: true
            activeFocusOnTab: true  // реагирование на перемещение между элементами ввода с помощью Tab
            focus: true  // элемент может получить фокус
            opacity: {if (IsConnectionOpen == true) {100} else {0}}
        }
    }
    }

    Button {
        id: butAdd
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.rightMargin: 8
        anchors.right:butEdit.left
        text: "Добавить"
        width: 100
        onClicked: windowAdd.show()
    }

    Button {
        id: butEdit
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.right: butDel.left
        anchors.rightMargin: 8
        text: "Редактировать"
        width: 100
        onClicked: {
            var nameRiv = rivList.currentItem.cafeData.nameOfCafe
            var lenghtRiv = rivList.currentItem.cafeData.lenghtOfCafe
            var flowRiv = rivList.currentItem.cafeData.flowOfCafe
            var runoffRiv = rivList.currentItem.cafeData.runoffOfCafe

            windowEdit.execute(nameRiv, lenghtRiv, flowRiv, runoffRiv, rivList.currentIndex)
        }
    }

    Button {
        id: butDel
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.right:parent.right
        anchors.rightMargin: 8
        text: "Удалить"
        width: 100
        enabled: rivList.currentIndex >= 0
        onClicked: del(rivList.currentIndex)
    }

        Label {
            id: labelArea
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 12
            anchors.left: parent.left
            //anchors.right: butAdd.left
            anchors.rightMargin: 8
            anchors.leftMargin: 8
            Layout.alignment: Qt.AlignRight  // выравнивание по правой стороне
            text: qsTr("Введите нужный тип кухни:")
        }
        TextField {
            id: textSelArea
            Layout.fillWidth: true
            placeholderText: qsTr("")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.leftMargin: 8
            anchors.left: labelArea.right
            anchors.rightMargin: 8
        }
        Button {
            id: butCount
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            //anchors.right:parent.right
            anchors.left: textSelArea.right
            anchors.leftMargin: 8
            text: "Подсчитать"
            width: 100
            enabled: textSelArea.text != ""
            onClicked: {

                windowAnswer.countCafes(textSelArea.text)
            }
        }


    DialogForAdd {
        id: windowAdd
    }
    DialogForEdit {
        id: windowEdit
    }
    DialogForAnswer {
        id: windowAnswer
    }
}

