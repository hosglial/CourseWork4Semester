#include "selectionwindow.h"
#include "ui_selectionwindow.h"
#include <QDebug>
SelectionWindow::SelectionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectionWindow)
{
    ///Конструктор устанавливает базовые настройки среды окна
    ui->setupUi(this);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background,Qt::white);
    this->setPalette(Pal);
}

SelectionWindow::~SelectionWindow()
{
    delete ui;
}

void SelectionWindow::on_OkButton_clicked()
{
    ///При нажатии на кнопку забирает данные из всех полей, записывает их в строку и отправляет в главное окно
    QString data;
    data += QString::number(ui->ResFr->value()) + ";";
    data += QString::number(ui->ResTo->value()) + ";";
    data += QString::number(ui->ButFrom->value()) + ";";
    data += QString::number(ui->ButTo->value()) + ";";
    data += QString::number(ui->PriceFrom->value()) + ";";
    data += QString::number(ui->PriceTo->value()) + ";";
    emit(sendDataFromSelection(data));
    this->close();
}
