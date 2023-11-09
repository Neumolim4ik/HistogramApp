#include <QChart>
#include <QChartView>
#include <QVBoxLayout>
#include "histogramwidget.h"
#include <QPainter>
#include <cmath>

HistogramWidget::HistogramWidget(QWidget *parent) : QWidget(parent), selectedParameter(ParameterType::RealPart) {}

void HistogramWidget::setParameter(ParameterType parameter) {
    selectedParameter = parameter;
    update();
}

void HistogramWidget::setData(const QVector<double> &data) {
    histogramData = data;
    maxValue = (histogramData.isEmpty()) ? 0.0 : *std::max_element(data.constBegin(), data.constEnd());
    update();
}

void HistogramWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setBrush(QBrush(Qt::blue));
    int barCount = histogramData.size();
    int barWidth = (barCount > 0) ? width() / barCount : 0;

    for (int i = 0; i < barCount; ++i) {
        int barHeight = 0;

        switch (selectedParameter) {
        case ParameterType::RealPart:
            barHeight = height() * (histogramData.at(i)) / maxValue;
            break;
        case ParameterType::ImaginaryPart:
            barHeight = height() * (histogramData.at(i)) / maxValue;
            break;
        case ParameterType::Magnitude:
            barHeight = height() * (histogramData.at(i)) / maxValue;
            break;
        case ParameterType::Phase:
            barHeight = height() * (histogramData.at(i)) / (2 * M_PI);
            break;
        }

        painter.drawRect(i * barWidth, height() - barHeight, barWidth, barHeight);
    }
}
