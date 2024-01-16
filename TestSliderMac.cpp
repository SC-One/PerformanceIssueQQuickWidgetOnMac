#include "TestSliderMac.h"
#include "./ui_TestSliderMac.h"
#include <QDial>
#include <QQuickWidget>
#include <QScrollBar>
#include <QSlider>
#include <QUrl>
#include <KnobWidget.h>
#include <QCheckBox>
#include <KnobQML.h>
#include "SameTableWidget.h"

static const QString Formatted = "%1: %2";
TestSliderMac::TestSliderMac(QWidget *parent)
    : QWidget(parent), ui(new Ui::TestSliderMac) {
    ui->setupUi(this);
    _waveform = new QQuickWidget(QUrl("qrc:/Comp.qml"), this);
    _waveform->setResizeMode(QQuickWidget::ResizeMode::SizeRootObjectToView);
    auto y= new SameTableWidget(this);
    ui->mainVlayout->insertWidget(0, y ,3);
    ui->mainVlayout->insertWidget(0, _waveform, 3);
    _waveform->setResizeMode(QQuickWidget::ResizeMode::SizeRootObjectToView);
    _waveform->setMaximumHeight(170);
}

TestSliderMac::~TestSliderMac() { delete ui; }
