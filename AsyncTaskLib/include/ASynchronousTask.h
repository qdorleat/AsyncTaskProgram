//
// Created by qdorleat on 29.11.22.
//

#ifndef ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H
#define ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include "TaskStateMachine.h"

class ASynchronousTask : public QThread,
                         public TaskStateMachine
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

	// Returns the state of the task.
	// Since the status is protected by a mutex, the getter cannot be const method
	State status();

protected:
	void run() override;
	void job();

signals:
	void stateChanged(State newState);

private:
	const unsigned _id;

	QMutex _mutex;
	QWaitCondition _condition;

	State _state {State::UNINITIALIZED};
};

#endif //ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H
