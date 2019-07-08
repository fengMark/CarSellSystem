#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QSplitter>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QKeySequence>
#include <QTableView>
#include <windows.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("汽车销售管理系统"));
    ui->stackedWidget->setCurrentIndex(0);
    QSqlQueryModel *factory = new QSqlQueryModel(this);
    factory->setQuery("select name from factory");
    ui->sellFactorycomboBox->setModel(factory);

    QSplitter *splitter = new QSplitter(ui->managePage);
    splitter->resize(700,360);
    splitter->move(0,50);
    splitter->addWidget(ui->toolBox);

    splitter->addWidget(ui->dailyList);
    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,1);
    CreateMenuBar();
    Sleep(2000);
}
void MainWindow::CreateMenuBar()
{
    manageAction = new QAction(tr("品牌车管理"),this);
    manageAction->setObjectName("manageAction");
    DataAction = new QAction(tr("导出销售记录"),this);
    DataAction->setObjectName("DataAction");
    chartAction = new QAction(tr("销售统计"),this);
    chartAction->setObjectName("chartAction");
    quitAction = new QAction(tr("退出"),this);
    quitAction->setObjectName("quitAction");

    manageAction->setShortcut(QKeySequence("Ctrl+M"));
    chartAction->setShortcut(QKeySequence("Ctrl+C"));
    quitAction->setShortcut(QKeySequence("Ctrl+Q"));
    DataAction->setShortcut(QKeySequence("Ctrl+O"));

    manageMenu = menuBar()->addMenu(tr("销售管理"));

    manageMenu->addAction(manageAction);
    manageMenu->addAction(chartAction);
    manageMenu->addSeparator();
    manageMenu->addAction(DataAction);
    manageMenu->addAction(quitAction);

    passwordMenu = menuBar()->addMenu(tr("修改密码"));

    connect(manageAction,SIGNAL(triggered(bool)),this,SLOT(manageMenu_clicked()));
    connect(chartAction,SIGNAL(triggered(bool)),this,SLOT(chartMenu_clicked()));
    connect(quitAction,SIGNAL(triggered(bool)),this,SLOT(quitMenu_clicked()));

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sellFactorycomboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1=="请选择厂家")
    {

    }else
    {
        ui->sellBrandcomboBox->setEnabled(true);
        QSqlQueryModel *mode = new QSqlQueryModel(this);
        mode->setQuery(QString("select name from brand where factory='%1'").arg(arg1));
        ui->sellBrandcomboBox->setModel(mode);
        ui->CancelpushButton->setEnabled(true);
    }
}

void MainWindow::on_sellBrandcomboBox_currentIndexChanged(const QString &arg1)
{
    ui->sellNumspinBox->setValue(0);
    ui->sellNumspinBox->setEnabled(false);
    ui->sellSumLineEdit->clear();
    ui->sellSumLineEdit->setEnabled(false);

    QSqlQuery query;
    query.exec(QString("select price from brand where name='%1' and factory='%2'").arg(arg1).arg(ui->sellFactorycomboBox->currentText()));
    query.next();
    ui->sellPricelineEdit->setEnabled(true);
    ui->sellPricelineEdit->setReadOnly(true);
    ui->sellPricelineEdit->setText(query.value(0).toString());

    query.next();
    int num = query.value(0).toInt();
    if(num==0)
    {
        QMessageBox::information(this,tr("提示"),tr("该品牌汽车已经售完"),QMessageBox::Ok);
    }else
    {
        ui->sellNumspinBox->setEnabled(true);
        ui->sellNumspinBox->setMaximum(num);
        ui->sellLastNumLabel->setText(tr("剩余数量：%1").arg("num"));
        ui->sellLastNumLabel->setVisible(true);
    }
}

void MainWindow::on_sellNumspinBox_valueChanged(int arg1)
{
    if(arg1==0)
    {
        ui->sellSumLineEdit->clear();
        ui->sellSumLineEdit->setEnabled(false);
        ui->OKpushButton->setEnabled(false);
    }else
    {
        ui->sellSumLineEdit->setEnabled(true);
        ui->sellSumLineEdit->setReadOnly(true);
        qreal sum = arg1*(ui->sellPricelineEdit->text().toInt());
        ui->sellSumLineEdit->setText(QString::number(sum));
        ui->OKpushButton->setEnabled(true);
    }
}

void MainWindow::on_OKpushButton_clicked()
{
    QString factory = ui->sellFactorycomboBox->currentText();
    QString name = ui->sellBrandcomboBox->currentText();

    int value = ui->sellNumspinBox->value();
    int last = ui->sellNumspinBox->maximum()-value;

    QSqlQuery query;
    query.exec(QString("select sell from brand where name='%1' and factory='%2'").arg(name).arg(factory));
    query.next();

    int sell = query.value(0).toInt()+value;

    QSqlDatabase::database().transaction();

    bool retVal = query.exec(QString("update brand set sell=%1,last=%2 where name='%3' and factory='%4'").arg(sell).arg(last).arg(name).arg(factory));

    if(retVal==true)
    {
        QSqlDatabase::database().commit();
        QMessageBox::information(this,tr("提示"),tr("购车成功！"),QMessageBox::Ok);
        on_CancelpushButton_clicked();
    }else
    {
        QSqlDatabase::database().rollback();
    }
}
void MainWindow::manageMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::chartMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::quitMenu_clicked()
{
    this->close();
}
void MainWindow::on_CancelpushButton_clicked()
{
    ui->sellFactorycomboBox->setCurrentIndex(0);
    ui->sellBrandcomboBox->clear();
}

//void MainWindow::createChartModelView()
//{
//    chartModel = new QStandardItemModel(this);
//    chartModel->setColumnCount(2);
//    chartModel->setHeaderData(0,Qt::Horizontal,QString("品牌"));
//    chartModel->setHeaderData(1,Qt::Horizontal,QString("销售数量"));
//    QSplitter *spliter = new QSplitter(ui->chartPage);
//    spliter->move(0,80);
//    QTableView *table = new QTableView;
//    PieView *pieChart = new PieView;
//    spliter->addWidget(table);
//    spliter->addWidget(pieChart);
//    spliter->setStretchFactor(0,1);
//    spliter->setStretchFactor(1,2);
//    table->setModel(chartModel);
//    QItemSelectionModel *selectionModel = new QItemSelectionModel(chartModel);
//    table->setSelectionModel(selectionModel);
//    pieChart->setSelectionModel(selectionModel);
//}

//void MainWindow::showChart()
//{
//    QSqlQuery query;
//    query.exec(QString("select name,sell from brand where factory='%1'").arg(ui->factoryCmbox->currentText()));
//    chartModel->removeRows(0,chartModel->rowCount(QModelIndex()),QModelIndex());

//    int row = 0;
//    while(query.next())
//    {
//        int r = qrand()%256;
//        int g = qrand()%256;
//        int b = qrand()%256;
//        chartModel->insertRows(row,1,QModelIndex());
//        chartModel->setData(chartModel->index(row,0,QModelIndex()),query.value(0).toString());
//        chartModel->setData(chartModel->index(row,1,QModelIndex()),query.value(1).toInt());
//        chartModel->setData(chartModel->index(row,0,QModelIndex()),QColor(r,g,b),Qt::DecorationRole);
//        row++;
//    }
//}



/*********************************************
 * 功能描述：xml文件读取写入
 * *******************************************/

QString MainWindow::getDataTime(DataTimeType type)
{
    QDateTime datetime = QDateTime::currentDateTime();
    QString date = datetime.toString("yyyy-MM-dd");
    QString time = datetime.toString("hh:mm");
    QString dateandtime = datetime.toString("yyyy-MM-dd hh:mm");
    if(type==ETIME) return time;
    else if(type==EDATE) return date;
    return dateandtime;
}

bool MainWindow::docRead()
{
    QFile file("data.xml");
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    if(!doc.setContent(&file))
    {
        file.close();
        return false;
    }
    file.close();
    return true;
}

bool MainWindow::docWrite()
{
    QFile file("data.xml");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        return false;
    }
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
    return true;
}

void MainWindow::writeXml()
{
    if(docRead())
    {
        QString currentDate = getDataTime(EDATE);
        QDomElement root = doc.documentElement();
        if(!root.hasChildNodes())
        {
            QDomElement date = doc.createElement(QString("日期"));
            QDomAttr curData = doc.createAttribute("date");
            curData.setValue(currentDate);
            date.setAttributeNode(curData);
            root.appendChild(date);
            createNodes(date);
        }else
        {
            QDomElement date = root.lastChild().toElement();
            if(date.attribute("date")==currentDate)
            {
                createNodes(date);
            }else
            {
                QDomElement date = doc.createElement(QString("日期"));
                QDomAttr curDate = doc.createAttribute("date");
                curDate.setValue(currentDate);
                date.setAttributeNode(curDate);
                root.appendChild(date);
                createNodes(date);
            }
        }
        docWrite();
    }
}
void MainWindow::createNodes(QDomElement &data)
{
    QDomElement time = doc.createElement("时间");
    QDomAttr curtime = doc.createAttribute("time");
    curtime.setValue(getDataTime(ETIME));
    time.setAttributeNode(curtime);
    data.appendChild(time);

    QDomElement factory = doc.createElement(QString("厂家"));
    QDomElement brand = doc.createElement(QString("品牌"));
    QDomElement price = doc.createElement(QString("报价"));
    QDomElement num = doc.createElement(QString("数量"));
    QDomElement sum = doc.createElement(QString("金额"));

    QDomText text;
    text = doc.createTextNode(QString("%1").arg(ui->sellFactorycomboBox->currentText()));
    factory.appendChild(text);

    text = doc.createTextNode(QString("%1").arg(ui->sellBrandcomboBox->currentText()));
    brand.appendChild(text);

    text = doc.createTextNode(QString("%1").arg(ui->sellPricelineEdit->text()));
    price.appendChild(text);

    text = doc.createTextNode(QString("%1").arg(ui->sellNumspinBox->value()));
    num.appendChild(text);

    text = doc.createTextNode(QString("%1").arg(ui->sellSumLineEdit->text()));
    sum.appendChild(text);

    time.appendChild(factory);
    time.appendChild(brand);
    time.appendChild(price);
    time.appendChild(num);
    time.appendChild(sum);
}
void MainWindow::showDailyList()
{
    ui->dailyList->clear();
    if(docRead())
    {
        QDomElement root = doc.documentElement();
        QString title = root.tagName();
        QListWidgetItem *titleItem = new QListWidgetItem;
        titleItem->setText(QString("-----------%1-----------").arg(title));
        titleItem->setTextAlignment(Qt::AlignCenter);
        ui->dailyList->addItem(titleItem);

        if(root.hasChildNodes())
        {
            QString currentDate = getDataTime(EDATE);
            QDomElement dateElement = root.lastChild().toElement();
            QString date = dateElement.attribute("date");

            if(date==currentDate)
            {
                ui->dailyList->addItem("");
                ui->dailyList->addItem(QString("日期：%1").arg(date));
                ui->dailyList->addItem("");

                QDomNodeList children = dateElement.childNodes();

                for(int uLoopi=0;uLoopi<children.count();uLoopi++)
                {
                    QDomNode node = children.at(uLoopi);
                    QString time = node.toElement().attribute("time");
                    QDomNodeList list = node.childNodes();

                    QString factory = list.at(0).toElement().text();
                    QString brand = list.at(1).toElement().text();
                    QString price = list.at(2).toElement().text();
                    QString num = list.at(3).toElement().text();
                    QString sum = list.at(4).toElement().text();

                    QString str = time+"出售"+brand+factory+" "+num+"辆，"+"成交价："+price+"万，共计："+sum+"万元";
                    QListWidgetItem *tempItem = new QListWidgetItem;
                    tempItem->setText("*******************************");
                    tempItem->setTextAlignment(Qt::AlignCenter);
                    ui->dailyList->addItem(tempItem);
                    ui->dailyList->addItem(str);
                }
            }
        }
    }
}

//void MainWindow::on_factoryCmbox_currentIndexChanged(const QString &arg1)
//{
//    if(arg1!="请选择厂家")
//    {
//        showChart();
//    }
//}

//void MainWindow::on_updateBtn_clicked()
//{
//    if(ui->factoryCmbox->currentText()!="请选择厂家")
//    {
//        showChart();
//    }
//}
