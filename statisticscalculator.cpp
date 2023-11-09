#include "statisticscalculator.h"
#include <cmath>

double StatisticsCalculator::calculateMean(const QVector<double> &data) {
    double sum = 0.0;
    for (const double &value : data) {
        sum += value;
    }
    return sum / data.size();
}

double StatisticsCalculator::calculateStandardDeviation(const QVector<double> &data) {
    double mean = calculateMean(data);
    double sum = 0.0;
    for (const double &value : data) {
        sum += (value - mean) * (value - mean);
    }
    return std::sqrt(sum / data.size());
}
