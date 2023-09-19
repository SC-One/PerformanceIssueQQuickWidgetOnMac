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

static const QString Formatted = "%1: %2";
TestSliderMac::TestSliderMac(QWidget *parent)
    : QWidget(parent), ui(new Ui::TestSliderMac) {
    ui->setupUi(this);
    {
        auto knob = new KnobWidget(this);
        ui->hz3->addWidget(knob);
        knob->setMaximumSize({100,100});
        connect(ui->mdt,&QCheckBox::toggled,this,[knob](bool toggled){
            knob->setTracking(toggled);
        });
    }
    {
        auto qmlKnob= new KnobQML(this);
        ui->hz3->addWidget(qmlKnob);
        qmlKnob->setMaximumSize({100,100});
        qmlKnob->setResizeMode(QQuickWidget::ResizeMode::SizeRootObjectToView);
    }
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
            auto knob = dynamic_cast<KnobWidget *>(widget);
            auto knobQML = dynamic_cast<KnobQML *>(widget);
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
            } else if (nullptr != knob) {
                connect(knob, &KnobWidget::valueChanged, this,
                        [this, id = reinterpret_cast<std::size_t>(knob)](int value) {
                    ui->textBrowser->append(Formatted.arg(id).arg(value));
                });
            } else if (nullptr != knobQML) {
                connect(knobQML, &KnobQML::valueChanged, this,
                        [this, id = reinterpret_cast<std::size_t>(knobQML)](float value) {
                    ui->textBrowser->append(Formatted.arg(id).arg(value));
                });
            }
        }
    }
}
