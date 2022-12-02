//
// Created by qdorleat on 29.11.22.
//

#ifndef ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H
#define ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

class ASynchronousTask : public QThread
{
	Q_OBJECT
public:
	ASynchronousTask(unsigned id);
	ASynchronousTask() = delete;
	ASynchronousTask(const ASynchronousTask& ) = delete;
	~ASynchronousTask();

	void pause();
	void resume();
	void stop();

public slots:
	void handleResults(const QString &);

protected:
	void run() override;
	void job();

signals:
	void operate(const QString &);

private:
	// incremental ID for ASynchronousTask objects;
	static unsigned ID;

	const unsigned _id;

	bool _shouldPause{false};
	QMutex _mutex;
	QWaitCondition _condition;
};

#endif //ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H
