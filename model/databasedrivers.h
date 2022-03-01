#ifndef DATABASEDRIVERS_H
#define DATABASEDRIVERS_H
#include <QHash>
#include <QMetaType>
#include "model/postgrerequestmaker.h"
static const QHash< QString,  QPair< QString,  int>> m_databaseDriverNameToDatabaseName({
                                                                                            {QStringLiteral("QDB2")	,   QPair<QString, int>(QStringLiteral("IBM DB2"), QMetaType::UnknownType)},
                                                                                            {QStringLiteral("QIBASE")  ,	QPair<QString, int>(QStringLiteral("Borland"), QMetaType::UnknownType)},
                                                                                            {QStringLiteral("QMYSQL")  ,	QPair<QString, int>(QStringLiteral("MySQL 7"), QMetaType::UnknownType)},
                                                                                            {QStringLiteral("QMYSQL3") ,	QPair<QString, int>(QStringLiteral("MySQL 3"), QMetaType::UnknownType)},
                                                                                            {QStringLiteral("QOCI")    ,	QPair<QString, int>(QStringLiteral("Oracle"), QMetaType::UnknownType)},
                                                                                            {QStringLiteral("QODBC")   ,	QPair<QString, int>(QStringLiteral("Microsoft SQL Server"), QMetaType::UnknownType)},
                                                                                            {QStringLiteral("QPSQL")   ,	QPair<QString, int>(QStringLiteral("PostgreSQL 9"), qRegisterMetaType<PostgreRequestsMaker*>())},
                                                                                            {QStringLiteral("QPSQL7")  ,	QPair<QString, int>(QStringLiteral("PostgreSQL 7"), qRegisterMetaType<PostgreRequestsMaker*>())},
                                                                                            {QStringLiteral("QSQLITE") ,	QPair<QString, int>(QStringLiteral("SQLite версии 3"), QMetaType::UnknownType)},
                                                                                            {QStringLiteral("QSQLITE2"),   QPair<QString, int>(QStringLiteral("SQLite версий 2"), QMetaType::UnknownType)},
                                                                                            {QStringLiteral("QTDS")    ,	QPair<QString, int>(QStringLiteral("Sybase"), QMetaType::UnknownType)},
                                                                                        });

#endif // DATABASEDRIVERS_H
