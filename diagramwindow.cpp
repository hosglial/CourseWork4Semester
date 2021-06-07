#include "diagramwindow.h"
#include "ui_diagramwindow.h"

static bool compare(const QPointF& first, const QPointF& second)//сравнивает первое занчение со следующим
{
    ///Сравнивает 2 QPointF по x, служит для правильной работы std::sort
    if (first.x() < second.x())
    {
        return true;
    }
    else if (first.x() > second.x())
    {
        return false;
    }
    else
    {
        if (first.y() < second.y())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

diagramWindow::diagramWindow(QWidget *parent, QLinkedList<Pad> *sp):
    QDialog (parent),
    ui(new Ui::diagramWindow)
{
    ///Настраивает окно, сортирует данные и строит диаграмму по Разрешение/Цена
    ///Диаграмма строится с помощью класса QChart
    ///  /// \param[in] *parent Указывает объект родитель для данного объекта
    ///  /// \param[in] *sp Указатель на список, из которого следует брать данные
    ui->setupUi(this);
    this->resize(1400,800);
    this->move(0,0);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background,Qt::white);
    this->setPalette(Pal);


    QLinkedList<Pad>::iterator iter;
    QList<QPointF> pointsList;
    int min=99999;
    int max = 0;
    for(iter = sp->begin();iter!=sp->end();iter++)
    {
        if(iter->getResolution() < min)
        {
            min = iter->getResolution();
        }
        if(iter->getResolution() > max)
        {
            max = iter->getResolution();
        }

    }


    for(iter = sp->begin();iter!=sp->end();iter++)
    {
        pointsList << QPointF(iter->getPrice(),iter->getResolution());
    }
    std::sort(pointsList.begin(), pointsList.end(),compare);

    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < sp->size(); i++)
    {
        series->append(pointsList.at(i));
    }


//    QValueAxis *axisY = new QValueAxis;
//    axisY->setMax(pointsList.last().rx());
//    axisY->setMin(pointsList.first().rx());
//    axisY->setTitleText("Price");
//    axisY->setTickCount(20);

//    QValueAxis *axisX = new QValueAxis;
//    axisX->setMax(max);
//    axisX->setMin(min);
//    axisX->setTitleText("Resolution");
//    axisY->setTickCount(20);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle(tr("Price/Resolution diagram"));
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(pointsList.first().rx(),pointsList.last().rx());
    chart->axes(Qt::Vertical).first()->setRange(min,max);
    chart->axes(Qt::Horizontal).first()->setTitleText(tr("Resolution"));
    chart->axes(Qt::Vertical).first()->setTitleText(tr("Price"));
//    chart->setAxisX(axisX);
//    chart->setAxisY(axisY);


    QChartView *chartView = new QChartView(chart);
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView);

}

diagramWindow::~diagramWindow()
{
    delete ui;
}
