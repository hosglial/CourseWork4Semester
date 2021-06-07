#ifndef EDITNOTEWINDOW_H
#define EDITNOTEWINDOW_H

#include <QDialog>
#include <pad.h>
#include <QDebug>
namespace Ui {
class EditNoteWindow;///Пространство имен ui отвечает за все, что связано с пользовательским интерфейсом
}
 ///Класс окна редактирования служит для изменения данных, хранящихся в двусвязном списке и отправки их в главное окно
class EditNoteWindow : public QDialog
{

    Q_OBJECT
signals:
    void sendDataFromEdit(Pad,bool);///<Сигнал отправки данных в главное окно
public:
    explicit EditNoteWindow(QWidget *parent = nullptr);
    ~EditNoteWindow();

private:
    Ui::EditNoteWindow *ui;///<Отвечает за все элементы, связанные с пользовательским интерфейсом
    bool add;///<Показывает, для чего была вызвана форма - добавления или редактирования элемента

public slots:
   void recieveDataToRedact(Pad temp,bool add);
private slots:
   void on_AcceptButton_clicked();
};

#endif // EDITNOTEWINDOW_H
