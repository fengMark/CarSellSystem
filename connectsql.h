#ifndef CONNECTSQL_H
#define CONNECTSQL_H
#include <QString>

extern bool createConnection();
extern bool changePwd(QString &oldPwd,QString &newPwd);

#endif // CONNECTSQL_H
