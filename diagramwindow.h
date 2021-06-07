#ifndef DIAGRAMWINDOW_H
#define DIAGRAMWINDOW_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QDialog>
#include <QLinkedList>
#include <QChartView>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QValueAxis>

#include "pad.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class diagramWindow; ///Пространство имен ui отвечает за все, что связано с пользовательским интерфейсом
}
///Класс окна диаграммы, служит для отображения графика, построенного с помощью QChart
class diagramWindow : public QDialog
{

    Q_OBJECT

public:
    explicit diagramWindow(QWidget *parent = nullptr, QLinkedList<Pad> *sp = nullptr);
    ~diagramWindow();

private:
    Ui::diagramWindow *ui;///<Отвечает за все элементы, связанные с пользовательским интерфейсом
};

#endif // DIAGRAMWINDOW_H
