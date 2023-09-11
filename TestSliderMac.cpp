#include "TestSliderMac.h"
#include "./ui_TestSliderMac.h"
#include <QDial>
#include <QQuickWidget>
#include <QScrollBar>
#include <QSlider>
#include <QUrl>

static const QString Formatted = "%1: %2";
TestSliderMac::TestSliderMac(QWidget *parent)
    : QWidget(parent), ui(new Ui::TestSliderMac) {
  ui->setupUi(this);
  _waveform = new QQuickWidget(QUrl("qrc:/Comp.qml"), this);
  _waveform->setResizeMode(QQuickWidget::ResizeMode::SizeRootObjectToView);
  connectToText(ui->mainVlayout);
  connect(ui->textBrowser, &QTextBrowser::textChanged, this, [this]() {
    QScrollBar *sb = ui->textBrowser->verticalScrollBar();
    sb->setValue(sb->maximum());
  });
  ui->mainVlayout->insertWidget(0, _waveform, 3);
  _waveform->setResizeMode(QQuickWidget::ResizeMode::SizeRootObjectToView);
}

TestSliderMac::~TestSliderMac() { delete ui; }

void TestSliderMac::connectToText(QLayout *layout) {
  if (!layout) {
    return;
  }

  for (int i = 0; i < layout->count(); ++i) {
    QLayoutItem *item = layout->itemAt(i);

    if (item->layout()) {
      connectToText(item->layout());
    } else if (item->widget()) {
      QWidget *widget = item->widget();
      auto dial = dynamic_cast<QDial *>(widget);
      auto slider = dynamic_cast<QSlider *>(widget);
      if (nullptr != dial) {
        connect(dial, &QDial::sliderMoved, this,
                [this, id = reinterpret_cast<std::size_t>(dial)](int value) {
                  ui->textBrowser->append(Formatted.arg(id).arg(value));
                });
      } else if (nullptr != slider) {
        connect(slider, &QSlider::valueChanged, this,
                [this, id = reinterpret_cast<std::size_t>(slider)](int value) {
                  ui->textBrowser->append(Formatted.arg(id).arg(value));
                });
      }
    }
  }
}
