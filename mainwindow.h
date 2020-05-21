#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QScrollArea>
#include <QScrollBar>
#include <QScroller>
#include "charttip.h"
#include <QDebug>

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
        void initChart();
        void addBarSet();
private slots:
    void sltTooltip(bool status, int index, QBarSet *barset);

private:
    Ui::MainWindow *ui;

    QChart*                         m_typeChart;
    QChartView*                     m_typeView;
    QBarCategoryAxis*               m_typeAxis;
    QValueAxis*                     m_typeAxisY;
    QBarSeries*                     m_barSeries;
    QBarSet*                        m_barSet;

    QStringList                     m_categories;
    ChartTip*                       m_tooltip;

};

#endif // MAINWINDOW_H
