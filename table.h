#ifndef TABLE1_H
#define TABLE1_H

#include <QObject>
#include <QtWidgets>
#include <pad.h>
/*!
 * \brief Класс таблицы
 * Класс для отображения, наследует основные элементы от QTableView
 * Переписан для реализации технологии DragnDrop
 */
class Table : public QTableView
{
    Q_OBJECT
public:
    Table(QWidget * parent = nullptr);
    void setSp(QLinkedList<Pad> *temp);


private slots:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
private:
    QLinkedList<Pad> *sp;///<Показывает, откуда брать данные
    QItemSelection *nowsel=nullptr;///<Указывает на текущий выделенный элемент
    QModelIndex index;///<Показывает, какой индекс был выделен
};

#endif // TABLE1_H
