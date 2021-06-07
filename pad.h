#ifndef PAD_H
#define PAD_H
#include "QString"
#include "QStringList"
#include <QLocale>
#include "QTranslator"
/*!
 * Класс служит для более удобного хранения данных об устройствах в виде объектов
  Содержит переменные характеристик устройства, а так же методы для работы с ними
*/
class Pad
{
public:
    ///Показывает версию порта USB устройста
    enum UsbProtocol
    {
        No,///<Нет подключения
        USB_2_0,///<Версия - USB 2.0
        USB_3_0,///<Версия - USB 3.0
        USB_3_1///<Версия - USB 3.1
    };
protected:
    int id;///<Id в списке
    QString Brand;///<Бренд
    QString Model;///<Модель
    int Resolution; ///<Разрешение сенсора
    int Buttons;///<Число кнопок
    UsbProtocol UsbType;///<Тип подключения usb
    double Price;///<Цена
    bool Gest;///<Поддержка жестов
public:
    Pad();//конструктор по умолчанию

    Pad(const QString cBrand,
        const QString cModel, const int cResolution,const int cButtons, const UsbProtocol cUsbType, const double cPrice, const bool cGest);

    Pad(const Pad& other);///<конструктор копирования

    ~Pad();///<деструктор

    void setBrand(const QString cBrand) { Brand = cBrand; }///<сетер(задает свойство объекта)
    void setModel(const QString cModel) { Model = cModel; }///<сетер(задает свойство объекта)
    void setResolution(const int    cResolution) { Resolution = cResolution; }///<сетер(задает свойство объекта)
    void setUsbType(const UsbProtocol cUsbType) { UsbType = cUsbType; }///<сетер(задает свойство объекта)
    void setPrice(const double    cPrice) { Price = cPrice; }///<сетер(задает свойство объекта)
    void setGest(const bool   cGest) { Gest = cGest; }///<сетер(задает свойство объекта)
    void setButtons(const int cButtons) {Buttons =cButtons;}///<сетер(задает свойство объекта)
    void setId(const int cId) {id = cId;}///<сетер(задает свойство объекта)
    void setData(Pad *obj);///<сетер(задает свойство объекта)
    QStringList getData();


    QString getBrand() const { return Brand; }///<гетер(получает свойство объекта)
    QString getModel() const { return Model; }///<гетер(получает свойство объекта)
    int getResolution() const { return Resolution; }///<гетер(получает свойство объекта)
    UsbProtocol getUsbType() const { return UsbType; }///<гетер(получает свойство объекта)
    double getPrice() const { return Price; }///<гетер(получает свойство объекта)
    bool getGest() const { return Gest; }///<гетер(получает свойство объекта)
    int getButtons() const {return Buttons;}///<гетер(получает свойство объекта)
    int getId() const {return id;}///<гетер(получает свойство объекта)
    static QString GtoS(bool value);
    static bool StoG(QString value);

};
Pad::UsbProtocol StoE(QString input);
QString EtoS(Pad::UsbProtocol input);




#endif // PAD_H
