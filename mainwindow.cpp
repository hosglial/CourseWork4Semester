#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextEdit"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{

    ///Конструктор занимается установкой базовых настроек, созданием объектов и линковкой сигналов и слотов
    //первичная установка и запоминание настроек
    ui->setupUi(this);
    getSettings();
    ui->menuBar->setVisible(ui->actionMenu_bar_on_off->isChecked());
    //белый цвет
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background,Qt::white);
    this->setPalette(Pal);


    //перетаскивание
    ui->tableView->viewport()->setAcceptDrops(true);
    ui->tableView->setDragDropMode(QAbstractItemView::NoDragDrop);
    ui->tableView->setSelectionMode(QTableWidget::SingleSelection);
    ui->tableView->setSelectionBehavior(QTableWidget::SelectRows);
    ui->tableView->setDropIndicatorShown(true);
    this->setAcceptDrops(1);


    menu = new QMenu(this);
    QAction * editDevice = new QAction(tr("Edit"), this);
    QAction * deleteDevice = new QAction(tr("Remove"), this);

    connect(editDevice, SIGNAL(triggered()), this, SLOT(slotSendDataToRedact()));
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(on_actionDelete_triggered()));

    menu->addAction(editDevice);
    menu->addAction(deleteDevice);


    connect(ui->actionEdit,SIGNAL(triggered()),this,SLOT(slotSendDataToRedact()));
    connect(ui->actionAdd,SIGNAL(triggered()),this,SLOT(slotAdd()));
    connect(ui->actionSearch,SIGNAL(triggered()),this,SLOT(on_SearchButton_clicked()));
    connect(ui->actionSelection,SIGNAL(triggered()),this,SLOT(on_SelectionButton_clicked()));
    connect(ui->actionRefresh,SIGNAL(triggered()),this,SLOT(on_ResetButton_clicked()));
    connect(ui->actionDiagram,SIGNAL(triggered()),this,SLOT(on_diagramButton_clicked()));


    sp = new QLinkedList<Pad>;
    ui->tableView->setSp(sp);


    TableUpdate();
}

MainWindow::~MainWindow()
{
    setSettings();
    delete ui;
}

void MainWindow::TableUpdate()
{
    ///Перестраивает таблицу, формирует модель и ставит ее в соответствие tableview, так же линкует контекстное меню
    ///и включает/выключает остальные элементы управления
    QLinkedList<Pad>::iterator iter;
    QString sGest;
    QStringList Header;
    int count=0;
    Header.push_back(tr("ID"));
    Header.push_back(tr("BRAND"));
    Header.push_back(tr("MODEL"));
    Header.push_back(tr("RESOLUTION"));
    Header.push_back(tr("BUTTONS"));
    Header.push_back(tr("USB TYPE"));
    Header.push_back(tr("PRICE"));
    Header.push_back(tr("GESTURE"));

    //Работа контекстного меню
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slotCustomMenuRequested(QPoint)));
    menu->actions().at(0)->setText(tr("Edit"));
    menu->actions().at(1)->setText(tr("Delete"));



    model = new QStandardItemModel();
    QStandardItem *item;
    model->setHorizontalHeaderLabels(Header);//применить заголовки к модели
    for (iter=sp->begin();iter!=sp->end();iter++)//формирование модели
    {
        iter->setId(count);//задаем id
        model->setItem(count,0,new QStandardItem(iter->getId()));
        for (int i=0;i<7;i++)
        {
            item = new QStandardItem(iter->getData().at(i));
            model->setItem(count,i+1,item);
        }
        count++;
    }

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(7,160);
    ui->tableView->resizeRowsToContents();
    ui->tableView->hideColumn(0);


    ui->actionEdit->setEnabled(!sp->isEmpty());
    ui->actionDelete->setEnabled(!sp->isEmpty());
    ui->lineEdit->setEnabled(!sp->isEmpty());
    ui->actionSearch->setEnabled(!sp->isEmpty());
    ui->actionSelection->setEnabled(!sp->isEmpty());
    ui->actionDiagram->setEnabled(!sp->isEmpty());
    ui->actionRefresh->setEnabled(!sp->isEmpty());
    ui->actionSave->setEnabled(!sp->isEmpty());
    ui->actionSaveAs->setEnabled(!sp->isEmpty());

    if(sp->isEmpty())
        ui->statusBar->showMessage("Open a file, or add a string",10);

}

//Основные функции

void MainWindow::on_actionOpen_triggered()
{
    ///Отвечает за открытие файла, парсинг данных, формирование объектов класса Pad, и заполнение ими двусвязного списка
    QString filename;
    QStringList slist;
    QString sline;
    filename = QFileDialog::getOpenFileName(this,tr("Open"));
    QFile file(filename);
    file.open( QIODevice::ReadOnly | QIODevice::Text );
    currentFile = filename;
    if(file.readLine().contains("Pad"))
        while(!file.atEnd())
        {
            sline=file.readLine();
            slist=sline.split(';');

            Pad *temp = new Pad(slist.at(0),
                                slist.at(1),
                                slist.at(2).toInt(),
                                slist.at(3).toInt(),
                                StoE(slist.at(4)),
                                slist.at(5).toDouble(),
                                slist.at(6).toInt()
                                );
            this->sp->push_back(*temp);
            free(temp);
        }
    else
    {
        QMessageBox::critical(this,tr("Error"),tr("Wrong file"));
    }
    TableUpdate();
}


void MainWindow::on_actionSaveAs_triggered()
{
    ///Метод сохранения данных "как"
    ///Выбирает имя файла и вызывает функцию сохранения
    currentFile = QFileDialog::getOpenFileName(this);
    on_actionSave_triggered();
}


void MainWindow::on_actionSave_triggered()//сохранить файл
{
    ///Отвечает за быстрое сохранение данных в файл
    QLinkedList<Pad>::iterator iter;
    QStringList slist;
    QString filename;
    if(currentFile.isEmpty())
        currentFile = QFileDialog::getOpenFileName(this);
    filename = currentFile;
    QFile file(filename);
    QTextStream writeStream(&file);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    int i=0;
    writeStream << "Pad\n";
    for(iter=sp->begin();iter!=sp->end();iter++,i++)
    {
        for(int i=0; i< iter->getData().size()-1;i++ )
            writeStream << iter->getData().at(i) << ";";
        writeStream<<iter->getGest()<<";";
        if(iter!=sp->end())
            writeStream<<"\n";
    }
    file.close();
}

void MainWindow::slotSendDataToRedact(bool add)//слот для отправки данных в EditWindow
{
    ///Слот отправки данных в форму редактирования
    /// \param[in] add показывает, что происходит в момент вызова - добавление записи или ее редактирование
    Pad *obj = new Pad();
    QLinkedList<Pad>::iterator iter;
    edit = new EditNoteWindow(this);
    connect(this,SIGNAL(sendDataToEdit(Pad,bool)),edit,SLOT(recieveDataToRedact(Pad,bool)));//connect сигнала отправки данных в edit
    connect(edit,SIGNAL(sendDataFromEdit(Pad,bool)),this,SLOT(slotRecieveData(Pad,bool)));//connect сигнала получения данных из edit
    for(iter=sp->begin();iter!=sp->end();iter++)
        if(iter->getId()==ui->tableView->currentIndex().row())
            obj = &(*iter);
    emit sendDataToEdit(*obj,add);
    edit->exec();
}

void MainWindow::slotRecieveData(Pad temp,bool add)//слот для получения данных из EditWindow и замене этих данных в списке
{
    ///Слот получения данных из формы редактирования
    /// \param[in] temp содержит данные, поступившие из формы в виде объекта
    /// \param[in] add указывает, что нужно сделать с данными - добавить или удалить
    QLinkedList<Pad>::iterator iter;
    if(add == true)
        sp->push_back(temp);
    else
        for(iter=sp->begin();iter!=sp->end();iter++)
            if(iter->getId()==ui->tableView->currentIndex().row())
            {
                iter->setData(&temp);
            }
    TableUpdate();
}

void MainWindow::on_actionDelete_triggered()//удаление
{
    ///Отвечает за удаление записи из двусвязного списка
    QLinkedList<Pad>::iterator iter;
    for(iter=sp->begin();iter!=sp->end();iter++)
        if(iter->getId()==ui->tableView->currentIndex().row())
        {
            sp->erase(iter);
        }
    TableUpdate();

}


//работа переводчика

void MainWindow::on_actionRussian_triggered()
{
    ///Установка русского языка
    currentLang="ru";
    translator.load(QString(":/Translations/ru.qm"));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    ui->actionDeutsch->setChecked(false);
    ui->actionEnglish->setChecked(false);
    ui->lineEdit->setText("");
    ui->tableView->clearSpans();
    TableUpdate();
}

void MainWindow::on_actionDeutsch_triggered()
{
    ///Установка немецкого языка
    currentLang="de";
    translator.load(QString(":/Translations/de.qm"));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    ui->actionRussian->setChecked(false);
    ui->actionEnglish->setChecked(false);;
    ui->lineEdit->setText("");
    ui->tableView->clearSpans();
    TableUpdate();
}

void MainWindow::on_actionEnglish_triggered()
{
    ///Установка английского языка
    currentLang="eng";
    translator.load(QString(":/Translations/eng.qm"));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    ui->actionRussian->setChecked(false);
    ui->actionDeutsch->setChecked(false);
    ui->lineEdit->setText("");
    ui->tableView->clearSpans();
    TableUpdate();

}


//работа Drag and Drop

void MainWindow::dragEnterEvent(QDragEnterEvent *e) //событие входа drag в окно
{
    ///Разрешает или запрещает перетаскивание в зависимости от того, есть ли в мышке данные
    if(e->mimeData()->hasText())
        e->setAccepted(true);
    else
        e->setAccepted(false);
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *e)//событие выхода drag из окна
{
    ///Разрешает выход drag из окна
    e->setAccepted(true);
}

void MainWindow::dropEvent(QDropEvent *e)
{
    ///Событие отпускания кнопки мыши, отвечает за взятие данных из события drag и их отправку в двусвязный список
    QStringList slist;
    QString line;
    line = e->mimeData()->data("data");
    slist = line.split(';');
    if(slist.isEmpty())
        return;
    Pad *temp = new Pad(slist.at(0),
                        slist.at(1),
                        slist.at(2).toInt(),
                        slist.at(3).toInt(),
                        StoE(slist.at(4)),
                        slist.at(5).toDouble(),
                        Pad::StoG(slist.at(6))
                        );
    temp->setId(this->sp->size());
    this->sp->push_back(*temp);
    TableUpdate();

}


//работа сохранения/восстановления настроек

void MainWindow::setSettings()
{
    ///Сохранение настроек окна в реестр при закрытии приложения
    QSettings settings("Mastermind","App");
    settings.beginGroup("w");
    settings.setValue("language",currentLang);  //сохраняется язык под ключом language
    settings.setValue("geometry", saveGeometry()); // сохраняется геометрия окна под ключом "geometry"
    settings.setValue("menu",QVariant(ui->actionMenu_bar_on_off->isChecked()));
    settings.endGroup();
}

void MainWindow::getSettings()
{
    ///Восстановление настроек интерфейса при открытии приложения
    QString lang;
    QSettings settings("Mastermind","App");
    settings.beginGroup( "w" );
    lang = settings.value("language").toString();//грузится язык под ключом language и сразу врубается переводчик
    translator.load(QString(lang));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    restoreGeometry(settings.value( "geometry", saveGeometry() ).toByteArray()); // восстанавление настроек геометрии окна по ключу "geometry"
    ui->actionMenu_bar_on_off->setChecked(settings.value("menu").toBool());
    settings.endGroup();
}


//слоты для работы меню, вызова окон итд...

void MainWindow::slotCustomMenuRequested(QPoint pos)//контекстное меню
{
    ///Слот вызова кастомного контекстного меню
    int row = ui->tableView->selectionModel()->currentIndex().row();
    if(ui->tableView->indexAt(pos).row() == row)
        if(!sp->isEmpty())
            if(row >=0)
                menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

void MainWindow::on_actionAbout_triggered()//о программе
{
    ///Вызов окна "О программе"
    QMessageBox::about(this,tr("About"),"Программа разработана: Щиголь Алексеем Анатольевичем.\nИКГ: ИЭУИС II-4.\nВариант: Тачпад.");
}

void MainWindow::on_SearchButton_clicked()//поиск
{
    ///Поиск данных и выделение их цветом
    QBrush brush(QColor(40,230,255));
    QString *str = new QString(ui->lineEdit->text());
    for (int i=0;i<model->rowCount();i++)
        for(int j=0;j<model->columnCount();j++)
        {
            QModelIndex index = model->index(i,j);
            if(index.data(Qt::DisplayRole).toString()==str)
                model->item(i,j)->setBackground(brush);
        }
    ui->tableView->setModel(model);
}

void MainWindow::on_ResetButton_clicked()//сброс
{
    ///Перестройка таблицы, служит для очисти данных от поиска или сброса подбора
    ui->lineEdit->setText("");
    ui->tableView->clearSpans();
    TableUpdate();
}

void MainWindow::on_SelectionButton_clicked()
{
    ///Отвечает за форму подбора, ее вызов и отправку данных в нее
    select = new SelectionWindow(this);
    select->setAttribute(Qt::WA_DeleteOnClose);
    connect(select,SIGNAL(sendDataFromSelection(QString)),this,SLOT(slotReciveDataFrSelection(QString)));
    select->exec();

}

void MainWindow::slotAdd()//добавить запись
{
    ///Вызывает слот отправки данных в форму редактирования с флагом true
    slotSendDataToRedact(true);
}

void MainWindow::on_actionNewWindow_triggered()//новое окно
{
    ///Создает новую копию этого же окна, таким образом позволяет открывать более 1 файла
    MainWindow *mainwindow = new MainWindow(this);
    mainwindow->setAttribute(Qt::WA_DeleteOnClose);
    mainwindow->show();
}

void MainWindow::slotReciveDataFrSelection(QString data)
{
    ///Слот получения данных из формы подбора. Проверяет все элементы из списка на соответствие и оставляет только те,
    ///которые подходят по параметрам
    QStringList list;
    int ResFr,ResTo;
    int ButFr,ButTo;
    double PriceFr,PriceTo;
    int count=0;
    QStandardItemModel *newmodel = new QStandardItemModel();
    QStandardItem *item;
    list = data.split(";");
    ResFr = list[0].toInt();
    ResTo = list[1].toInt();
    ButFr = list[2].toInt();
    ButTo = list[3].toInt();
    PriceFr = list[4].toInt();
    PriceTo = list[5].toInt();
    QAbstractItemModel *model = ui->tableView->model();
    if(PriceTo == 0.0)
        PriceTo = 999999;
    if(ResTo == 0)
        ResTo = 999999;
    if(ButTo == 0)
        ButTo = 999999;

    for(int i=0;i<sp->size();i++)
    {
        if(model->data(model->index(i,3)) >= ResFr && model->data(model->index(i,3)) <= ResTo &&
                model->data(model->index(i,4)) >= ButFr && model->data(model->index(i,4)) <= ButTo &&
                model->data(model->index(i,6)) >= PriceFr && model->data(model->index(i,6)) <= PriceTo)
        {
            for (int j = 0;j<7;j++)
            {
                QString data;
                data = model->data(model->index(i,j)).toString();
                item = new QStandardItem(data);
                newmodel->setItem(count,j,item);
            }
            count++;
        }

    }
    ui->tableView->clearSpans();
    ui->tableView->setModel(newmodel);
    QVector<int> vec;
}

void MainWindow::on_diagramButton_clicked()
{
    ///Вызывает окно с диаграммой
    diagram = new diagramWindow(this,sp);
    diagram->setAttribute(Qt::WA_DeleteOnClose);
    diagram->exec();

}


void MainWindow::on_actionMenu_bar_on_off_triggered(bool checked)
{
    ///Отвечает за скрытие/показ панели основного меню
    /// \param[in] checked показывает, нажата ли кнопка
    ui->menuBar->setVisible(checked);
}


