//
// Created by qdorleat on 29.11.22.
//

#ifndef ASYNCTASKPROGRAM_TASK_H
#define ASYNCTASKPROGRAM_TASK_H

#include <QObject>

class Task : public QObject
{
	Q_OBJECT

public slots:
	void runJob();

signals:
	void resultReady(const QString &result);
};

#endif //ASYNCTASKPROGRAM_TASK_H
