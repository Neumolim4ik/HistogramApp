#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "statisticscalculator.h"
#include "histogramwidget.h"
#include "BinaryDataReader.h"
#include <QComboBox>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openFile();
    void updateHistogram();
private:
    BinaryDataReader binaryReader;
    HistogramWidget *histogramWidget;
    QComboBox *parameterComboBox;
    QLabel *meanLabel;
    QLabel *stdDeviationLabel;

    StatisticsCalculator statisticsCalculator;
};

#endif
