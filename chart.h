#ifndef CHART_H
#define CHART_H

#include <QWidget>

#include <QtCharts>
namespace Ui {
class Chart;
}

class Chart : public QWidget
{
  Q_OBJECT

public:
  explicit Chart(QWidget* parent = nullptr);
  ~Chart();
  void setData(const QVector<double>& data);

private:
  QLineSeries* lineSeries;
  QChart* chart;
  QChartView* chartView;
  Ui::Chart* ui;
};

#endif // CHART_H
