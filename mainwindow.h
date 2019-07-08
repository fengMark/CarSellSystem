#ifndef MAINWINDOW_H
#define MAINWINDOW_H

enum DataTimeType{ETIME,EDATE,EDATEANDTIME};

#include <QMainWindow>
#include <QMenuBar>
#include <QDomElement>
#include <QDomDocument>
#include <QDateTime>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void manageMenu_clicked();
    void chartMenu_clicked();
    void quitMenu_clicked();
private slots:
    void on_sellFactorycomboBox_currentIndexChanged(const QString &arg1);

    void on_sellBrandcomboBox_currentIndexChanged(const QString &arg1);

    void on_sellNumspinBox_valueChanged(int arg1);

    void on_OKpushButton_clicked();

    void on_CancelpushButton_clicked();

//    void on_factoryCmbox_currentIndexChanged(const QString &arg1);

//    void on_updateBtn_clicked();

private:
    QString getDataTime(DataTimeType type);
    bool docRead();
    bool docWrite();
    void writeXml();
    void createNodes(QDomElement &data);
    void showDailyList();


//    void createChartModelView();
//    void showChart();


private:
    void CreateMenuBar();
    QDomDocument doc;
    Ui::MainWindow *ui;
    QMenu *manageMenu;
    QMenu *passwordMenu;
    QAction *manageAction;
    QAction *chartAction;
    QAction *quitAction;
    QAction *DataAction;
    QStandardItemModel *chartModel;
};

#endif // MAINWINDOW_H
