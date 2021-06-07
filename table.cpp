#include "table.h"
    ///Конструктор служит для первоначальной инициализации параметров объекта
    /// /// \param[in] *parent Указывает объект родитель для данного объекта
Table::Table(QWidget *parent): QTableView (parent)
{
    this->acceptDrops();
}

    ///Устанавливает указатель на список, из которого следует брать данные
void Table::setSp(QLinkedList<Pad> *temp)
{
    sp = temp;
}
///Переопределенное событие нажатия клавиши мыши, запоминает текущий выделенный элемент
void Table::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        this->selectRow(this->indexAt(event->pos()).row());
        nowsel = new QItemSelection(this->currentIndex(),this->currentIndex());
    }
    index = this->indexAt(event->pos());
}
///Переопределенное событие передвигания кнопки мыши
///Если элемент, выделенный в mousePressEvent доступен для перетаскивания, запоминает его и записывает в mimeData, и далее передает
///управление событию перетаскивания
void Table::mouseMoveEvent(QMouseEvent *event)
{

    QLinkedList<Pad>::iterator iter;
    QItemSelection sel;

    if(!sp->isEmpty())
        if((event->buttons() & Qt::LeftButton) && index.isValid() && !index.data().isNull())
        {
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData();
            QString sGest;
            QString str;

            for(iter=sp->begin();iter!=sp->end();iter++)
                if(iter->getId()==this->currentIndex().row())
                {
                    switch(static_cast<int>(iter->getGest()))
                    {
                    case 1:sGest="Поддерживает жесты";break;
                    case 0:sGest="Не поддерживает жесты";break;
                    }
                    str =   iter->getBrand() + ";"+
                            iter->getModel() + ";"+
                            QString::number(iter->getResolution()) + ";"+
                            QString::number(iter->getButtons()) + ";"+
                            EtoS(iter->getUsbType()) + ";"+
                            QString::number(iter->getPrice()) + ";"+
                            sGest;
                }
            QByteArray as = QByteArray::fromBase64((str.toUtf8()).toBase64());
            mimeData->setData("data",as);
            mimeData->setText(str);
            mimeData->setParent(this);
            drag->setMimeData(mimeData);
            drag->exec();
            return;
        }
}
