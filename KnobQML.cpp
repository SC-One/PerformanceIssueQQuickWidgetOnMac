#include "KnobQML.h"
#include <QQmlContext>
#include <QQmlEngine>

KnobQML::KnobQML(QWidget *parent)
    : QQuickWidget(parent)
{
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    setSource(QUrl("qrc:/DialQML.qml"));

    QQmlContext *context = rootContext();
    context->setContextProperty("knobQML", this);

    _value = 0.0;
}

void KnobQML::setValue(float value)
{
    if (qFuzzyCompare(_value, value))
        return;

    _value = value;
    emit valueChanged(_value);
}
