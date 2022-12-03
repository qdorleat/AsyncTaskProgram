//
// Created by qdorleat on 29.11.22.
//

#ifndef ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H
#define ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

enum State
{
	UNINITIALIZED,
	RUNNING,
	PAUSED,
	STOPPED,
	COMPLETED
};


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

protected:
	void run() override;
	void job();

	bool isTransitionAllowed(State from, State to);
	void transition(State desiredState, std::function<void()> const& callBack);

private:
	const unsigned _id;

	QMutex _mutex;
	QWaitCondition _condition;

	State _state {State::UNINITIALIZED};
	static QMap<State, QSet<State>> transitions;
};

#endif //ASYNCTASKPROGRAM_ASYNCHRONOUSTASK_H
