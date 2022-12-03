//
// Created by qdorleat on 03.12.22.
//

#ifndef ASYNCTASKPROGRAM_TASKSTATEMACHINE_H
#define ASYNCTASKPROGRAM_TASKSTATEMACHINE_H

#include <QMap>
#include <functional>

enum State
{
	UNINITIALIZED,
	RUNNING,
	PAUSED,
	STOPPED,
	COMPLETED,
};

class TaskStateMachine
{
protected:

	QString toString(State);
	bool isTransitionAllowed(State from, State to);
	void transition(State currentState, State desiredState, std::function<void()> const& callBack);

private:
	static QMap<State, QSet<State>> transitions;
};


#endif//ASYNCTASKPROGRAM_TASKSTATEMACHINE_H
