#include "widgets/frequencymanagerwidget.h"
#include <QLineEdit>

extern int slider_steps;
extern double pi;


void FrequencyManagerWidget::updateLabel()
{
    std::string text = "F: " + std::to_string(getFrequency())+ " Hz";
    this->currentFreq->setText(QString::fromStdString(text));
}

FrequencyManagerWidget::FrequencyManagerWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    slider = new QSlider(Qt::Horizontal, this);
    minFreq = new QLineEdit("30", this);
    maxFreq = new QLineEdit("120", this);

    currentFreq= new QLabel(this);
    currentFreq->setFixedWidth(120);
    slider->setMinimum(0);
    slider->setMaximum(slider_steps);

    minFreq->setFixedWidth(80);
    maxFreq->setFixedWidth(80);
    //minFreq->setValidator(new QDoubleValidator(20, 1000, 2, this));
    //minFreq->setValidator(new QDoubleValidator(20, 1000, 2, this));


    layout->addWidget(minFreq);
    layout->addWidget(slider);
    layout->addWidget(maxFreq);
    layout->addWidget(currentFreq);
    this->setLayout(layout);

    connect(slider, &QSlider::valueChanged,
            this, &FrequencyManagerWidget::updateLabel);
    connect(slider, &QSlider::valueChanged,
            this, &FrequencyManagerWidget::sliderValueChanged);

    this->updateLabel();
}

double FrequencyManagerWidget::getFrequency()
{
    double minF = minFreq->text().toDouble();
    double maxF = maxFreq->text().toDouble();
    double step = (maxF-minF)/slider_steps;

    double frequency = minF + slider->value()*step;
    return frequency;
}

double FrequencyManagerWidget::getAngularFrequency()
{
    return 2*pi*getFrequency();
}
