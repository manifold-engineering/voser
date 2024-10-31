#ifndef FREQUENCYMANAGERWIDGET_H
#define FREQUENCYMANAGERWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>

class FrequencyManagerWidget : public QWidget
{
    Q_OBJECT
protected:
    QHBoxLayout *layout;
    QSlider *slider;
    QLineEdit *minFreq;
    QLineEdit *maxFreq;
    QLabel *currentFreq;

private slots:
    void updateLabel();
    void sliderValueChanged(){emit frequencyChanged();}

public:
    explicit FrequencyManagerWidget(QWidget *parent = nullptr);
    double getFrequency();
    double getAngularFrequency();

signals:
    void frequencyChanged();

};

#endif // FREQUENCYMANAGERWIDGET_H
