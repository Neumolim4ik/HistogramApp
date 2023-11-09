#ifndef BINARYDATAREADER_H
#define BINARYDATAREADER_H

#include <QFile>
#include <QByteArray>
#include <QVector>
#include <complex>

using QComplex = std::complex<double>;

enum class ParameterType {
    RealPart,
    ImaginaryPart,
    Magnitude,
    Phase
};

class BinaryDataReader {
public:
    BinaryDataReader();
    BinaryDataReader(const QString &fileName);
    bool openFile();
    QByteArray readData(int size);
    QVector<QComplex> readComplexData(int size);
    QVector<double> calculateParameter(const QVector<QComplex> &data, ParameterType parameter);
    void closeFile();
    double calculateMean();
    double calculateStandardDeviation();

private:
    QFile file;
    QVector<double> readNumbers;
};

#endif
