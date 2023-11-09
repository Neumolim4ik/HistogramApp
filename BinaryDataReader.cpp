#include "BinaryDataReader.h"
#include <iostream>
#include <cmath>

BinaryDataReader::BinaryDataReader() : file() { }
BinaryDataReader::BinaryDataReader(const QString &fileName) : file(fileName) {}

bool BinaryDataReader::openFile() {
    return file.open(QIODevice::ReadOnly);
}

QVector<QComplex> BinaryDataReader::readComplexData(int size) {
    QVector<QComplex> complexData;
    for (int i = 0; i < size; ++i) {
        // Считываем два числа (действительную и мнимую части) из файла и добавляем их в вектор
        if (file.atEnd()) {
            break;
        }
        double realPart, imaginaryPart;
        file.read(reinterpret_cast<char*>(&realPart), sizeof(double));
        file.read(reinterpret_cast<char*>(&imaginaryPart), sizeof(double));
        complexData.append(QComplex(realPart, imaginaryPart));
    }
    return complexData;
}

double BinaryDataReader::calculateMean() {
    if (readNumbers.isEmpty()) {
        return 0.0;
    }
    double sum = std::accumulate(readNumbers.constBegin(), readNumbers.constEnd(), 0.0);
    return sum / readNumbers.size();
}

double BinaryDataReader::calculateStandardDeviation() {
    if (readNumbers.isEmpty()) {
        return 0.0;
    }
    double mean = calculateMean();
    double variance = 0.0;
    for (double number : readNumbers) {
        variance += std::pow(number - mean, 2);
    }
    variance /= readNumbers.size();
    return std::sqrt(variance);
}

QVector<double> BinaryDataReader::calculateParameter(const QVector<QComplex> &data, ParameterType parameter) {
    QVector<double> parameterData;
    for (const QComplex &complexValue : data) {
        switch (parameter) {
        case ParameterType::RealPart:
            parameterData.append(complexValue.real());
            break;
        case ParameterType::ImaginaryPart:
            parameterData.append(complexValue.imag());
            break;
        case ParameterType::Magnitude:
            parameterData.append(abs(complexValue));
            break;
        case ParameterType::Phase:
            parameterData.append(arg(complexValue));
            break;
        }
    }
    return parameterData;
}

void BinaryDataReader::closeFile() {
    file.close();
}

QByteArray BinaryDataReader::readData(int size) {
    return file.read(size);
}
