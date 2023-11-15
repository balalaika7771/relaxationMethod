#include "chart.h"
#include "ui_chart.h"

Chart::Chart(QWidget* parent)
  : QWidget(parent)
  , ui(new Ui::Chart)
{
  ui->setupUi(this);

  // Create line series and chart
  lineSeries = new QLineSeries(this);
  chart = new QChart();
  chart->addSeries(lineSeries);
  chart->setTitle("Selection root plot ");

  // Create chart view
  chartView = new QChartView(chart, this);
  chartView->setRenderHint(QPainter::Antialiasing);

  // Set up layout
  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(chartView);

  // Set up axis
  QValueAxis* axisX = new QValueAxis;
  axisX->setLabelFormat("%.2f");
  axisX->setTitleText("number of iteration");
  chart->addAxis(axisX, Qt::AlignBottom);
  lineSeries->attachAxis(axisX);

  QValueAxis* axisY = new QValueAxis;
  axisY->setTitleText("x value ");
  chart->addAxis(axisY, Qt::AlignLeft);
  lineSeries->attachAxis(axisY);

  // Set up legend
  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignBottom);
}

Chart::~Chart()
{
  delete ui;
}

void
Chart::setData(const QVector<double>& data)
{
  // Clear existing data
  lineSeries->clear();

  // Add data to the line series
  for (int i = 0; i < data.size(); ++i) {
    lineSeries->append(i, data[i]);
  }
  // Set axis ranges based on the data
  if (!data.isEmpty()) {
    QValueAxis* axisX =
      qobject_cast<QValueAxis*>(chart->axes(Qt::Horizontal).at(0));
    QValueAxis* axisY =
      qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).at(0));

    if (axisX && axisY) {
      axisX->setRange(0, data.size() - 1);
      axisY->setRange(*std::min_element(data.constBegin(), data.constEnd()),
                      *std::max_element(data.constBegin(), data.constEnd()));
    }
  }
  chart->addSeries(lineSeries);
}
