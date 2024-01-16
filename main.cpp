#include "TestSliderMac.h"

#include <QApplication>
#include <Thirdparty/NiceFramelessWindow/framelesswindow/framelesswindow.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  CFramelessWindow window;
  auto x = new TestSliderMac(&window);
  window.setCentralWidget(x);
  window.showMaximized();
  return a.exec();
}
