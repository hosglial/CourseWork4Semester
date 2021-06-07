#include "editnotewindow.h"
#include "ui_editnotewindow.h"

EditNoteWindow::EditNoteWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditNoteWindow)
{
    ///Производит первоначальную настройку интерфейса и инициализацию переменных
    /// \param[in] *parent Указывает объект родитель для данного объекта
    ui->setupUi(this);
    ui->retranslateUi(this);


    QPalette Pal(palette());
    Pal.setColor(QPalette::Background,Qt::white);
    this->setPalette(Pal);
}

EditNoteWindow::~EditNoteWindow()
{
    delete ui;
}


void EditNoteWindow::recieveDataToRedact(Pad temp,bool add)
{
    ///Получает данные из главного окна и в случае если происходит редактирование раскидывает их по полям ввода
    /// \param[in] temp содержит данные, полученные из главного окна
    /// \param[in] add показывает, происходит редактирование или добавление
    this->add = add;
    if(add != true)
    {
        this->setWindowTitle(tr("Edit"));
        ui->InBrand->setText(temp.getBrand());
        ui->InModel->setText(temp.getModel());
        ui->InPrice->setValue(temp.getPrice());
        ui->UsbBox->setCurrentIndex(temp.getUsbType());
        ui->ButtonBox->setValue(temp.getButtons());
        ui->GestBox->setCurrentIndex(temp.getGest());
        ui->inResolution->setValue(temp.getResolution());
    }
    else
    {
    this->setWindowTitle(tr("Add"));
    }
}

void EditNoteWindow::on_AcceptButton_clicked()
{
    ///Прин нажатии на кнопу подтверждения формирует объект и отправляет его обратно в главное окно
    Pad *temp = new Pad(ui->InBrand->text(),
                        ui->InModel->text(),
                        ui->inResolution->value(),
                        ui->ButtonBox->value(),
                        StoE(ui->UsbBox->currentText()),
                        ui->InPrice->value(),
                        ui->GestBox->currentIndex()
                        );

    emit sendDataFromEdit(*temp,add);
    this->close();
}
