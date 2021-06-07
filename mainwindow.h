#pragma once
#include <QMainWindow>

#include <QLinkedList>
#include <fstream>
#include <sstream>
#include <QFile>
#include <QFileDialog>
#include <QList>
#include <QTranslator>
#include <QLocale>
#include <QtDebug>
#include <QTextStream>
#include <QSettings>
#include "editnotewindow.h"
#include "pad.h"
#include "table.h"
#include "selectionwindow.h"
#include "diagramwindow.h"

namespace Ui
{
class MainWindow; ///Пространство имен ui отвечает за все, что связано с пользовательским интерфейсом
}


   ///Класс главного окна, содержит реализацию бОльшей части методов, отвечающих за работу программы
class MainWindow : public QMainWindow
{

    Q_OBJECT
signals:
    void sendDataToEdit(Pad obj,bool add);///<сигнал отправки данных в окно редактирования
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void TableUpdate();


private slots:
    void on_actionOpen_triggered();

    void slotAdd();

    void on_actionDelete_triggered();

    void on_actionAbout_triggered();

    void on_actionSave_triggered();

    void slotSendDataToRedact(bool add=false);

    void slotCustomMenuRequested(QPoint pos);

    void on_actionRussian_triggered();

    void on_actionDeutsch_triggered();

    void on_actionEnglish_triggered();

    void on_actionNewWindow_triggered();

    void on_SearchButton_clicked();

    void setSettings();

    void getSettings();

    void on_ResetButton_clicked();

    void on_SelectionButton_clicked();

    void on_diagramButton_clicked();    


    void on_actionMenu_bar_on_off_triggered(bool checked);

    void on_actionSaveAs_triggered();

private:
    Ui::MainWindow *ui;///<Отвечает за элементы пользовательского интерфейса
    QLinkedList<Pad> *sp;///<Хранит данные
    EditNoteWindow *edit;///<Динамически созданнное окно редактирования
    QTranslator translator;///<Переводчик
    QString currentLang;///<Строка, указывающая текущий язык программы
    SelectionWindow *select;///<Динамически созданное окно подбора
    diagramWindow *diagram;///<Динамически созданное окно диаграммы
    QMenu *menu;///<Динамически созданное контекстное меню
    QStandardItemModel *model;///<Модель для QTableView
    QString currentFile;///<<Имя текущего открытого файла

public slots:
    void slotRecieveData(Pad temp,bool add);
    void slotReciveDataFrSelection(QString data);

protected:
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dragLeaveEvent(QDragLeaveEvent *e);
    virtual void dropEvent(QDropEvent *e);
};
