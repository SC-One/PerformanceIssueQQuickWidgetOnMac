#ifndef KNOBWIDGET_H
#define KNOBWIDGET_H

#include <QWidget>

class KnobWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KnobWidget(QWidget *parent = nullptr);

    inline bool getTracking() const;
    void setTracking(bool value);

signals:
    void valueChanged(int value);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    inline void notifyValue();
private:
    int value;
    int maxValue;
    int knobAngle;
    bool tracking=false;
public slots:
    void setValue(int newValue);
};

#endif // KNOBWIDGET_H
