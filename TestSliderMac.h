#ifndef TESTSLIDERMAC_H
#define TESTSLIDERMAC_H

#include <QHBoxLayout>
#include <QLayout>
#include <QQuickWidget>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class TestSliderMac;
}
QT_END_NAMESPACE

class TestSliderMac : public QWidget {
  Q_OBJECT

public:
  TestSliderMac(QWidget *parent = nullptr);
  ~TestSliderMac();

private:
  Ui::TestSliderMac *ui;
  QQuickWidget *_waveform;
};
#endif // TESTSLIDERMAC_H
