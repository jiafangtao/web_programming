#! /usr/bin/env python3

import sys
from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlApplicationEngine


if __name__ == '__main__':
	app = QGuiApplication(sys.argv)
	engine = QQmlApplicationEngine()
	with open("simple.qml") as f:
		engine.loadData(f.read().encode("utf-8"))
		if not engine.rootObjects():
			sys.exit(-1)

		exit_code = app.exec()
		del engine

		sys.exit(exit_code)
