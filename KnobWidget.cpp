#include "KnobWidget.h"
#include <QPainter>
#include <cmath>
#include <QMouseEvent>
#include <QtAlgorithms>
#include <QtMath>

KnobWidget::KnobWidget(QWidget *parent)
    : QWidget(parent), value(0), maxValue(100), knobAngle(0)
{
    setMinimumSize(100, 100);
}

void KnobWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(Qt::darkGray);
    painter.drawEllipse(rect());

    painter.translate(width() / 2, height() / 2);
    painter.rotate(knobAngle);
    painter.setBrush(Qt::red);
    painter.drawEllipse(-10, -40, 20, 80);
}

void KnobWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        qreal angle = qAtan2(event->y() - height() / 2, event->x() - width() / 2) * 180 / M_PI;
        knobAngle = static_cast<int>(angle);
        update();
    }
}

void KnobWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        qreal angle = qAtan2(event->y() - height() / 2, event->x() - width() / 2) * 180 / M_PI;
        knobAngle = static_cast<int>(angle);
        if(getTracking())
            notifyValue();
        update();
    }
}

void KnobWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    notifyValue();
}

void KnobWidget::notifyValue()
{
    value = static_cast<int>((knobAngle + 360) % 360 * (maxValue / 360.0));
    emit this->valueChanged(value);

}

bool KnobWidget::getTracking() const
{
    return tracking;
}

void KnobWidget::setTracking(bool value)
{
    tracking = value;
}

void KnobWidget::setValue(int newValue)
{
    if (newValue >= 0 && newValue <= maxValue)
    {
        value = newValue;
        knobAngle = static_cast<int>((value / static_cast<float>(maxValue)) * 360);
        update();
    }
}
