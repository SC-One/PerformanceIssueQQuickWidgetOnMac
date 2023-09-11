#include "TestSliderMac.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  TestSliderMac w;
  w.show();
  return a.exec();
}
