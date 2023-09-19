// knobqml.h
#ifndef KNOBQML_H
#define KNOBQML_H

#include <QQuickWidget>

class KnobQML : public QQuickWidget
{
    Q_OBJECT

public:
    explicit KnobQML(QWidget *parent = nullptr);

signals:
    void valueChanged(float value);

public slots:
    void setValue(float value);

private:
    float _value;
};

#endif // KNOBQML_H
