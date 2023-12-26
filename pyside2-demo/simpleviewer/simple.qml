import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
	width: 300
	height: 200
	visible: true
	title: "Hello World"

	readonly property list<string> texts: ["Hello World", "Hallo Welt", "Hola Mundo"]

	function setText() {
		var i = Math.round(Math.random() * 2)
		text.text = texts[i]
	}

	ColumnLayout {
		anchors.fill: parent

		Text {
			id: text
			text: "uninitialized"
			Layout.alignment: Qt.AlignCenter
		}
		Button {
			text: "Click"
			Layout.alignment: Qt.AlignCenter
			onClicked: setText()
		}
	}
}
