#include "connectsql.h"
#include<QtSql>
#include<QDebug>
#include<QString>
#include<QFile>
#include<QIODevice>
#include<QDomDocument>

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("F:\\CarMamagentSystem\\CarMamagentSystem\\carInfo.db");
    db.setUserName("markfeng");
    db.setPassword("123456789");

    if(!db.open())
    {
        qDebug()<<"open error"<<endl;
        return false;
    }
    QSqlQuery query(db);
    //创建厂家表
    bool flag = query.exec("create table if not exists  factory("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "name VARCHAR)");
    query.exec("insert into factory values(0,'请选择厂家')");
    query.exec("insert into factory values(1,'一汽大众')");
    query.exec("insert into factory values(2,'二汽胜龙')");
    query.exec("insert into factory values(3,'上海大众')");

    flag = query.exec("create table if not exists brand(id varchar primary key,name varchar,factory varchar,price int,sum int,sell int,last int)");
    if(flag==false)
    {
        qDebug()<<"open error"<<endl;
    }
    flag=query.exec("insert int brand values('01','奥迪A6','一汽大众','36','50','10','40')");
         query.exec("insert int brand values('02','捷达','一汽大众','36','50','10','40')");
         query.exec("insert int brand values('03','宝马','一汽大众','36','50','10','40')");
         query.exec("insert int brand values('04','标致307','一汽大众','36','50','10','40')");
         query.exec("insert int brand values('05','奥迪A6','一汽大众','36','50','10','40')");
         query.exec("insert int brand values('06','奥迪A6','一汽大众','36','50','10','40')");
         query.exec("insert int brand values('07','奥迪A6','一汽大众','36','50','10','40')");

    flag = query.exec("create table if not exists password(pwd varchar primary key)");
    if(flag==false)
    {
        qDebug()<<"open error"<<endl;
    }
    query.exec("insert into password values('123456')");

    return true;
}


bool createXml()
{
    QFile file("data.xml");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        return false;
    }
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\"encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    QDomElement root = doc.createElement(QString("日销售清单"));
    doc.appendChild(root);
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
    return true;
}


