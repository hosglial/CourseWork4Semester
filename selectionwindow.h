#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H

#include <QDialog>

namespace Ui {
class SelectionWindow;
}
///Окно подбора содержит методы, реализующие подбор устройства по нескольким параметрам
class SelectionWindow : public QDialog
{

    Q_OBJECT

public:
    explicit SelectionWindow(QWidget *parent = nullptr);
    ~SelectionWindow();

private:
    Ui::SelectionWindow *ui;

private slots:
    void on_OkButton_clicked();
signals:
    void sendDataFromSelection(QString data);///<сигнал отправки данных в основное окно
};

#endif // SELECTIONWINDOW_H
