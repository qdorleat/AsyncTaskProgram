//
// Created by qdorleat on 29.11.22.
//

#ifndef ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H
#define ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H

#include <QThread>

class Task;

class ASynchronousTask : public QObject
{
	Q_OBJECT
public:
	ASynchronousTask();
	~ASynchronousTask();

	void start();
	void pause();
	void stop();

public slots:
	void handleResults(const QString &);

signals:
	void operate(const QString &);

private:
	// incremental ID for ASynchronousTask objects;
	static unsigned ID;
	// Working thread in charge of running the job
	QThread _workingThread;
	Task* task;
};

#endif //ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H
