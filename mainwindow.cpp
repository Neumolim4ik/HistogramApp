#include "mainwindow.h"
#include "BinaryDataReader.h"
#include "histogramwidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Complex Data Histogram");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Select a binary file:");
    layout->addWidget(label);

    QPushButton *openButton = new QPushButton("Open File");
    layout->addWidget(openButton);

    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);

    parameterComboBox = new QComboBox(this);
    parameterComboBox->addItem("Real Part");
    parameterComboBox->addItem("Imaginary Part");
    parameterComboBox->addItem("Magnitude");
    parameterComboBox->addItem("Phase");
    layout->addWidget(parameterComboBox);

    connect(parameterComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateHistogram()));

    histogramWidget = new HistogramWidget(this);
    layout->addWidget(histogramWidget);

    setCentralWidget(new QWidget(this));
    centralWidget()->setLayout(layout);

    meanLabel = new QLabel("Mean: N/A", this);
    layout->addWidget(meanLabel);

    stdDeviationLabel = new QLabel("Standard Deviation: N/A", this);
    layout->addWidget(stdDeviationLabel);
}

void MainWindow::openFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open Binary File");
    if (filePath.isEmpty()) {
        return;
    }

    BinaryDataReader binaryReader(filePath);

    if (binaryReader.openFile()) {
        QVector<double> data;
        QByteArray rawBinaryData = binaryReader.readData(100);

        // Преобразуем бинарные данные в числа (зависит от формата бинарных данных)
        for (int i = 0; i < rawBinaryData.size(); ++i) {
            double number = static_cast<double>(static_cast<unsigned char>(rawBinaryData.at(i)));
            data.append(number);
        }

        double mean = statisticsCalculator.calculateMean(data);
        double stdDeviation = statisticsCalculator.calculateStandardDeviation(data);

        // Отображение результатов в виджетах
        meanLabel->setText("Mean: " + QString::number(mean));
        stdDeviationLabel->setText("Standard Deviation: " + QString::number(stdDeviation));


        histogramWidget->setData(data);

        binaryReader.closeFile();

        QMessageBox::information(this, "Success", "Binary data read successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to open the file.");
    }
}

void MainWindow::updateHistogram() {
    ParameterType selectedParameter = static_cast<ParameterType>(parameterComboBox->currentIndex());

    QVector<QComplex> complexData = binaryReader.readComplexData(100); // Чтение комплексных данных, регулируйте размер при необходимости
    QVector<double> parameterData = binaryReader.calculateParameter(complexData, selectedParameter);

    histogramWidget->setParameter(selectedParameter);
    histogramWidget->setData(parameterData);
}
