#include "mainwindow.h"
#include "ui_mainwindow.h"

//CToolTip *g_toolTip;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , m_tooltip(0)
{
    ui->setupUi(this);
    initChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initChart()
{
    m_typeChart = new QChart();
    m_typeChart->setAnimationOptions(QChart::SeriesAnimations);

    m_barSet = new QBarSet("eg");
    m_barSet->setLabelColor(QColor(0,0,0));
    m_barSeries = new QBarSeries(m_typeChart);
    m_barSeries->setLabelsVisible(true);
    m_barSeries->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    connect(m_barSeries, SIGNAL(hovered(bool, int, QBarSet*)), this, SLOT(sltTooltip(bool, int, QBarSet*)));

//    QLineSeries *series = new QLineSeries;
//    connect(series, SIGNAL(hovered(QPointF, bool)), this, SLOT(sltTooltip(QPointF,bool)));//折线图

    m_typeChart->addSeries(m_barSeries);
    m_typeChart->setTitle("历史记录");
    m_typeAxis = new QBarCategoryAxis();
    m_typeChart->createDefaultAxes();
    m_typeChart->setAcceptTouchEvents(true);
    m_typeChart->setAxisX(m_typeAxis, m_barSeries);

    m_typeAxisY = new QValueAxis;
    m_typeAxisY->setRange(0, 10);
    m_typeAxisY->setTickCount(10);     //设置多少格
    m_typeAxisY->setMinorTickCount(5); //设置每格小刻度线的数目

    m_typeChart->setAxisY(m_typeAxisY, m_barSeries);

    m_typeChart->legend()->setVisible(true);
    m_typeChart->legend()->setAlignment(Qt::AlignBottom);
    m_typeChart->legend()->hide();
    m_typeView = new QChartView();
    m_typeView->setChart(m_typeChart);

    ui->widget->layout()->addWidget(m_typeView);

    addBarSet();
}

void MainWindow::addBarSet()
{
    *m_barSet << 1 << 2 << 3 << 4 << 5 << 6;
    m_barSeries->append(m_barSet);
    m_categories  << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jan";
    m_typeAxis->append(m_categories);//
}

void MainWindow::sltTooltip(bool status, int index, QBarSet *barset)
{
    if (m_tooltip == 0)
        m_tooltip = new ChartTip(m_typeChart);

    if (status) {
        m_tooltip->setText("X: "+m_categories.at(index)+"\n"+QString("Y: %2 ").arg(barset->at(index)));
        QPointF point(index, barset->at(index));
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    }
    else {
        m_tooltip->hide();
    }
}


