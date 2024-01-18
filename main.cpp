#include "TestSliderMac.h"

#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <CustomModel.h>
#include <Thirdparty/NiceFramelessWindow/framelesswindow/framelesswindow.h>

#define PURE_QML "qrc:/TestPureQMLTable/TestPureQMLTable.qml"

int main(int argc, char *argv[]) {
#ifdef PURE_QML

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication a(argc, argv);
    qmlRegisterType<CustomModel>("TestNameSpace", 1, 0, "CustomModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral(PURE_QML));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &a, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

#else
  QApplication a(argc, argv);
  CFramelessWindow window;
  auto x = new TestSliderMac(&window);
  window.setCentralWidget(x);
  window.showMaximized();
#endif
    return a.exec();
}
