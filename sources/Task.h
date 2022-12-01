//
// Created by qdorleat on 29.11.22.
//

#ifndef ASYNCTASKPROGRAM_TASK_H
#define ASYNCTASKPROGRAM_TASK_H

#include <QObject>

#include <QMutex>
#include <QWaitCondition>

class Task : public QObject
{
	Q_OBJECT

public:
	void stop();
	void resume();

public slots:
	void runJob();

signals:
	void resultReady(const QString &result);

private:
	bool _shouldStop {false};

	QMutex _mutex;
	QWaitCondition _condition;
};

#endif //ASYNCTASKPROGRAM_TASK_H
