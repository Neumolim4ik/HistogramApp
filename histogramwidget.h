#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include "BinaryDataReader.h"


class HistogramWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HistogramWidget(QWidget *parent = nullptr);
    void setData(const QVector<double>& data);
    void setParameter(ParameterType parameter);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<double> histogramData;
    ParameterType selectedParameter;
    double maxValue = 0.0;
};

#endif
