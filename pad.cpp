#include "pad.h"
Pad::Pad() :Brand(""), Model(""), Resolution(0),Buttons(0), UsbType(No), Price(0.0), Gest(0)
{
    ///конструктор по умолчанию инициализирует пустые и нулевые переменные
}

Pad::Pad
(
        const QString cBrand,
        const QString cModel, const int cResolution,const int cButtons, const UsbProtocol cUsbType, const double cPrice, const bool cGest
        ) :// конструктор с параметром
    Brand(cBrand),
    Model(cModel),
    Resolution(cResolution),
    Buttons(cButtons),
    UsbType(cUsbType),
    Price(cPrice),
    Gest(cGest)
{
    ///Параметрический конструктор инициализирует все перемеенные класса
    /// \param[in] cBrand Входное значение бренда
    /// \param[in] cModel Входное значение модели
    /// \param[in] cResolution Входное значение разрешения
    /// \param[in] cButtons Входное значение числа кнопок
    /// \param[in] cUsbType Входное значение типа USB
    /// \param[in] cPrice Входное значение цены
    /// \param[in] cGest Входное значение наличия жестов
}

Pad::Pad(const Pad& other) :
    Brand(other.Brand),
    Model(other.Model),
    Resolution(other.Resolution),
    Buttons(other.Buttons),
    UsbType(other.UsbType),
    Price(other.Price),
    Gest(other.Gest)
{
    ///Копирует данные одного объекта в другой
    /// \param[in] other копируемый объект
    /// \return отредактированный  объект

}

Pad::~Pad() {}

void Pad::setData(Pad *obj)
{
    Brand = obj->Brand;
    Model = obj->Model;
    Resolution = obj->Resolution;
    Buttons = obj->Buttons;
    UsbType = obj->UsbType;
    Price = obj->Price;
    Gest = obj->Gest;
}

QStringList Pad::getData()
{
    ///Получает данные из объекта в виде QStringList
    ///Служит для более удобного доступа к данным
    QStringList slist;
    slist.append(Brand);
    slist.append(Model);
    slist.append(QString::number(Resolution));
    slist.append(QString::number(Buttons));
    slist.append(EtoS(UsbType));
    slist.append(QString::number(Price));
    slist.append(GtoS(Gest));
    return slist;
}

QString Pad::GtoS(bool value)
{
    ///Переводит булевскую переменную в текст
    /// \param[in] value входящая переменная
    /// \return возвращает 2 вида текста в зависимости от значения value
    if(value == true)
        return "Поддерживает";
    else
        return "Не поддерживает";
}

bool Pad::StoG(QString value)
{
    ///Переводит текст в булевскую переменную
    /// /// \param[in] value входящая переменная
    /// \return возвращает true либо false в зависимости от значения value
    if(value.contains("Поддерживает"))
        return true;
    else
        return false;
}

Pad::UsbProtocol StoE(QString input)
{
    ///Переводит строки в перечисление USBProtocol
    /// \param[in] input входная строка
    /// \return Соответствующее входной строке значение в перечислении
    if(input.contains("No"))
        return Pad::No;
    if(input.contains("USB_2_0"))
        return Pad::USB_2_0;
    if(input.contains("USB_3_0"))
        return Pad::USB_3_0;
    if(input.contains("USB_3_1"))
        return Pad::USB_3_1;
    return Pad::No;
}



QString EtoS(Pad::UsbProtocol input)
{
     ///Переводит USBProtocol в строки
     ///\param[in] input входная переменная
     /// \return Строку, соответствующую входной переменной
    switch (input) {
    case Pad::No:return "No";
    case Pad::USB_2_0: return "USB_2_0";
    case Pad::USB_3_0: return "USB_3_0";
    case Pad::USB_3_1: return "USB_3_1";
    }
    return "No";
}
