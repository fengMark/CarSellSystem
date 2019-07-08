#include "mainwindow.h"
#include <QApplication>
#include "connectsql.h"
#include "logindialog.h"
#include <QSplashScreen>
#include <QPixmap>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString dir = QCoreApplication ::applicationDirPath();
    qDebug()<<dir<<endl;
    QPixmap pixmap(dir+"/APPUpLoading.jpg");
    QSplashScreen plash(pixmap);
    plash.show();
    plash.showMessage(QObject::tr("Setting up the main window..."),Qt::AlignRight | Qt::AlignTop, Qt::blue);
    MainWindow w;
    LoginDialog logindialog;
    if(!createConnection())
    {
        return 0;
    }
    if(logindialog.exec()==QDialog::Accepted)
    {
        plash.finish(&logindialog);
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }
}
