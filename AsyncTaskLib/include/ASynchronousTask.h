//
// Created by qdorleat on 29.11.22.
//

#ifndef ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H
#define ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H

#include <QFile>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include "TaskStateMachine.h"
#include "Definitions.h"

class ASynchronousTask : public QThread,
                         public TaskStateMachine
{
	Q_OBJECT
public:
	ASynchronousTask(unsigned id);
	ASynchronousTask() = delete;
	ASynchronousTask(const ASynchronousTask& ) = delete;
	virtual ~ASynchronousTask();

	void pause();
	float progress();
	void resume();
	void stop();
	virtual QString type() = 0;

	// Returns the state of the task.
	// Since the status is protected by a mutex, the getter cannot be const method
	State status();

protected:
	void run() override;

	// Job specification of the task
	virtual void job() = 0;

signals:
	void stateChanged(State newState);

private:
	// Setups task environment
	bool setup();

protected:
	QFile _file;

private:
	const unsigned _id;

	QMutex _mutex;
	QWaitCondition _condition;

	State _state {State::UNINITIALIZED};
	float _progress {0.0f};
};

#endif //ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H
