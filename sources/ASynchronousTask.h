//
// Created by qdorleat on 29.11.22.
//

#ifndef ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H
#define ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

class Task;

class ASynchronousTask : public QThread
{
	Q_OBJECT
public:
	ASynchronousTask();
	~ASynchronousTask();

public slots:
	void handleResults(const QString &);

protected:
	void run() override;

signals:
	void operate(const QString &);

private:
	// incremental ID for ASynchronousTask objects;
	static unsigned ID;
	// Working thread in charge of running the job
	QThread _workingThread;
	Task* task;

	QMutex _mutex;
	QWaitCondition _condition;
};

#endif //ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H
