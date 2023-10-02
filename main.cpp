#include "TestSliderMac.h"

#include <QApplication>
#include <Thirdparty/NiceFramelessWindow/framelesswindow/framelesswindow.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  CFramelessWindow window;
  auto x = new TestSliderMac(&window);
  window.setCentralWidget(x);
//  w.show();
  window.setGeometry(100,100,770,500);
  window.show();
  return a.exec();
}
