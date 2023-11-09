#ifndef STATISTICSCALCULATOR_H
#define STATISTICSCALCULATOR_H

#include <QVector>

class StatisticsCalculator
{
public:
    double calculateMean(const QVector<double> &data);
    double calculateStandardDeviation(const QVector<double> &data);
};

#endif
